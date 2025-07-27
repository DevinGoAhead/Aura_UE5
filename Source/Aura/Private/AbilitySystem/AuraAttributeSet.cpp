// Copyright  By Devin


#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGameplayTags.h"

#include "GameFramework/PlayerController.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet() {
	const auto& AuraGameplayTagsInstance = FAuraGameplayTags::Get();
	// Primary Attribute
	// 函数名直接用作函数指针
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Primary_Strength, GetStrengthAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Primary_Vigor, GetVigorAttribute);

	// Secondary Attribute
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_Armor, GetArmorAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagToAttribute.Add(AuraGameplayTagsInstance.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
}

// Returns properties that are replicated for the lifetime of the actor channel
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// COND_None, 不需要满足任何条件即可复制
	// REPNOTIFY_Always, 即使客户端与服务端的值完全相同, 也会复制(本项目我们需要对复制行为响应, 而不只是复制, 因而Always)
	// REPNOTIFY_Changed, 只有客户端与服务端值不同, 才会被复制

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always); // 将 Health 填入 OutLifetimeProps
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	// SecondaryAttributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}


void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	//UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange"));
	if (Attribute == GetHealthAttribute()){
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute()){
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
	else {/*...*/}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProp;
	SetEffectProperties(Data, &EffectProp);
	auto EvaluatedAttribute = Data.EvaluatedData.Attribute;
	if (EvaluatedAttribute == GetHealthAttribute()){
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (EvaluatedAttribute == GetManaAttribute()){
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	else {/*...*/}
	UE_LOG(LogTemp, Warning, TEXT("Health BaseValue = %f, CurrentValue = %f"), 
			GetHealthAttribute().GetGameplayAttributeData(this)->GetBaseValue(),
			GetHealthAttribute().GetGameplayAttributeData(this)->GetCurrentValue());
}

// Vital Attributes
// 当属性复制到客户端会调用该类型函数, 可执行一些复制后逻辑
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	// 辅助宏，用于 RepNotify 函数，处理将被客户端预测修改的属性(权威属性, 经过服务端确认的属性)
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

// Primary Attributes
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const{
	// used in RepNotify functions to handle attributes that will be predictively modified by clients.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}
void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}
void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}
void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

// SecondaryAttributes
void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}
void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}
void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}
void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}
void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}
void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}
void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}
void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}
void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data,
                                            FEffectProperties* EffectProp) {
	if (const auto EffectContext = Data.EffectSpec.GetEffectContext().Get(); EffectContext) { // Get 是获取指针
		if (EffectProp->InstigatorACS = EffectContext->GetInstigatorAbilitySystemComponent(); IsValid(EffectProp->InstigatorACS)) { // Effect 的最终来源的 ASC
			if (const auto ActorInfo = EffectProp-> InstigatorACS->AbilityActorInfo; ActorInfo.IsValid()) {
				CompleteEffectPropertiesFromInfo(ActorInfo.Get(), EffectProp->InstigatorController, EffectProp->InstigatorAvatarActor, EffectProp->InstigatorAvatarCharacter);
			}
		}
	}
	EffectProp->TargetACS = &Data.Target;
	if (const auto ActorInfo = EffectProp->TargetACS->AbilityActorInfo; ActorInfo.IsValid()){
		CompleteEffectPropertiesFromInfo(ActorInfo.Get(), EffectProp->TargetController, EffectProp->TargetAvatarActor, EffectProp->TargetAvatarCharacter);
	}
}

void UAuraAttributeSet::CompleteEffectPropertiesFromInfo(const FGameplayAbilityActorInfo* ActorInfo, AController*& Controller, AActor*& Actor, ACharacter*& Character){
	if (!ActorInfo) return;
	Controller = Cast<AController>(ActorInfo->PlayerController.Get()); // 这里为了方便, 下面可能会指向非APlayerController 类型对象
	Actor = ActorInfo->AvatarActor.Get();
	// 如果二者都非 nullptr, 那么就不会继续向下执行if了
	// 如果二者均为 nullptr, 那么也不会向下执行if了

	// 接下来, Controller ⇄ Pawn 双向补全逻辑

	// 从 Controller 推 Pawn
	// 这里是 AController* 指向APlayerController 类型对象
	// AActor* 指向APawn 或 ACharacter
	if (Controller && !Actor){ // 说明 AvatarActor 一定是玩家角色, 且由于某些原因 AvatarActor 获取失败
		if (Actor = Controller->GetCharacter(); !Actor){
			Actor = Controller->GetPawn();
		}
	}
	// 从Pawn 推 Controller
	// AvatarActor一定非玩家角色? 不一定!
	// AvatarActor 一定指向 APawn 系? 不一定!
	else if (!Controller && Actor){
		if (const auto Pawn = Cast<APawn>(Actor); Pawn){ 
			Controller = Pawn->GetController();
		}
		// 先不处理仅处理 非APawn 系的对象 的情况, 但可以肯定的是 Controller 一定为 nullptr
		else {}
	}
	Character = Cast<ACharacter>(Actor);
}
