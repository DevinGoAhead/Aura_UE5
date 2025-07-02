// Copyright  By Devin


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet() {
	Health = 20.f;
	MaxHealth = 100.f;
	Mana = 30.f;
	MaxMana = 100.f;
}

// 将 OnRep_Health 注册到引擎的复制系统
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// COND_None, 不需要满足任何条件即可复制
	// REPNOTIFY_Always, 即使客户端与服务端的值完全相同, 也会复制(本项目我们需要对复制行为响应, 而不只是复制, 因而Always)
	// REPNOTIFY_Changed, 只有客户端与服务端值不同, 才会被复制
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

//
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

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	// 辅助宏，用于 RepNotify 函数，处理将被客户端预测修改的属性(权威属性, 经过服务端确认的属性)
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
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
