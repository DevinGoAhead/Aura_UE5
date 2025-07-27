// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"
class UAuraUserWidget;
struct FOnAttributeChangeData;

// DataTable 的行类型
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MessageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Image = nullptr; // 如果需要显示图片
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowDelegate, const FUIWidgetRow&, Row); //


/**
 * 
 */
// 蓝图类型意味着我们可以在事件图中把它当作一种类型使用, 比如执行类型转换
// 蓝图化意味着可以基于这个类创建蓝图, 且这种性质可以继承
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitValue() override;
	virtual void BindCallbacksToDependencies() override;
protected:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnAttributeChangedDelegate OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnAttributeChangedDelegate OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnAttributeChangedDelegate OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Atribute")
	FOnAttributeChangedDelegate OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Message")
	FMessageWidgetRowDelegate MessageWidgetRow;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> MsgWidgetDataTable;
protected:
};
