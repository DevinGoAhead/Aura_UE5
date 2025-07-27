// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraASBlueprintLibrary.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class AAuraHUD;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraASBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(APlayerController* PC);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeWidgetController(APlayerController* PC);
private:
	static AAuraHUD* GetWigetControllerParams(APlayerController* PC,
			APlayerState*& OutPS, UAbilitySystemComponent*& OutASC, UAttributeSet*& OutAS);
};
