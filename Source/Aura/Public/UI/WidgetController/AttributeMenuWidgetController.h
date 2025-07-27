// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AuraAttributeDataAsset.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAuraAttributeDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, InAttributeInfo);
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoDelegate;
private:
	UPROPERTY(EditDefaultsOnly)
	UAuraAttributeDataAsset* AttributeDataAsset;
};
