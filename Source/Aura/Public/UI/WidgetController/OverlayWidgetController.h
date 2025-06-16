// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
/**
 * 
 */
// 蓝图类型意味着我们可以在事件图中把它当作一种类型使用, 比如执行类型转换
// 蓝图化意味着可以基于这个类创建蓝图
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitValue() override;
	virtual void BindCallbacksToDependencies() override;
protected:
	void HealthChanged(const FOnAttributeChangeData& NewData) const;
	void MaxHealthChanged(const FOnAttributeChangeData& NewData) const;

	void ManaChanged(const FOnAttributeChangeData& NewData) const;
	void MaxManaChanged(const FOnAttributeChangeData& NewData) const;
protected:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnMaxManaChangedSignature OnMaxManaChanged;

};
