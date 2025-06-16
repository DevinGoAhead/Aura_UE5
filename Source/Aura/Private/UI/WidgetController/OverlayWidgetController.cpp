// Copyright  By Devin


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitValue() {
	Super::BroadcastInitValue();
	const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth()); // 调用观察者列表中的所有注册函数并将 AuraAttributeSet->GetHealth() 作为参数传入
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana()); 
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies() {
	Super::BindCallbacksToDependencies();
	const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	// 获取 Health 的元数据, 封装进  FOnAttributeChangeData
	// 将 HealthChanged 注册到委托列表
	// 初始化时赋值不会被监听到, 需要满足下面两个条件之一：
	// 或属性值通过 GameplayEffect 应用 修改
	// 或显式调用 SetBaseValue() 或 SetCurrentValue() 并带有 bTriggerDelegate = true // 几乎不会这样使用
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& NewData) const{
	OnHealthChanged.Broadcast(NewData.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& NewData) const{
	OnMaxHealthChanged.Broadcast(NewData.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& NewData) const {
	OnManaChanged.Broadcast(NewData.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& NewData) const {
	OnMaxManaChanged.Broadcast(NewData.NewValue);
}
