// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams{
	GENERATED_BODY()
	
	FWidgetControllerParams() = default;
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	void InitWidgetController(const FWidgetControllerParams& WCP);
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitValue();
	virtual void BindCallbacksToDependencies();
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
};
