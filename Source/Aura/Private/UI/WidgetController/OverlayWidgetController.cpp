// Copyright  By Devin


#include "UI/WidgetController/OverlayWidgetController.h"
#include "Aura/DebugMacros.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

// 在 AAuraHUD::InitOverlay 中被调用
void UOverlayWidgetController::BroadcastInitValue() {
	Super::BroadcastInitValue();
	const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth()); // 调用观察者列表中的所有注册函数并将 AuraAttributeSet->GetHealth() 作为参数传入
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana()); 
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

// 在 AAuraHUD::InitOverlayWidgetController 中被调用
void UOverlayWidgetController::BindCallbacksToDependencies() {
	Super::BindCallbacksToDependencies();
	const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	// 获取 Health 的元数据, 封装进  FOnAttributeChangeData
	// 将 HealthChanged 注册到委托列表
	// 初始化时赋值不会被监听到, 需要满足下面两个条件之一才会被监听：
	// 或属性值通过 GameplayEffect 应用 修改
	// 或显式调用 SetBaseValue() 或 SetCurrentValue() 并带有 bTriggerDelegate = true // 几乎不会这样使用
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& NewData){
			OnHealthChanged.Broadcast(NewData.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& NewData){
		OnMaxHealthChanged.Broadcast(NewData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& NewData){
		OnManaChanged.Broadcast(NewData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& NewData){
		OnMaxManaChanged.Broadcast(NewData.NewValue);
	});
	// EffectAssetTags 是
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTagContainer){
		for (const auto& Tag : AssetTagContainer){
			//FString Msg = FString::Printf(TEXT("GE Tag: %s"), GetData(Tag.ToString()));
			//ADD_SCREEN_DEBUG(-1 ,Msg);
			// 在现有的GamplayTag List 中查找是否有匹配的 Tag, 若有则return, 若无则return一个 empty
			FGameplayTag MsgTag = FGameplayTag::RequestGameplayTag(FName("Messages"));
			// 假设 Tag = Messages.HealthPotion, Tag.MatchesTag(Messages), true
			// 假设 Tag = Messages, Tag.MatchesTag(Messages.HealthPotion), false
			if (MsgWidgetDataTable && Tag.MatchesTag(MsgTag)){
				if (auto Row = MsgWidgetDataTable->FindRow<FUIWidgetRow>(Tag.GetTagName(), TEXT("Found Nothing")); Row){
					MessageWidgetRow.Broadcast(*Row);
				}
			}
		}
	});
}
