// Copyright  By Devin


#include "AbilitySystem/AuraASBlueprintLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraASBlueprintLibrary::GetOverlayWidgetController(APlayerController* PC){
	APlayerState* PS; UAbilitySystemComponent* ASC; UAttributeSet* AS;
	if (auto AuraHUD = GetWigetControllerParams(PC, PS, ASC, AS); AuraHUD){
		return AuraHUD->GetOverlayWidgetController({PC, PS, ASC, AS});
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraASBlueprintLibrary::GetAttributeWidgetController(APlayerController* PC){
	APlayerState* PS; UAbilitySystemComponent* ASC; UAttributeSet* AS;
	if (auto AuraHUD = GetWigetControllerParams(PC, PS, ASC, AS); AuraHUD){
		return AuraHUD->GetAttributeMenuWidgetController({PC, PS, ASC, AS});
	}
	return nullptr;
}

AAuraHUD* UAuraASBlueprintLibrary::GetWigetControllerParams(APlayerController* PC, APlayerState*& OutPS,
	UAbilitySystemComponent*& OutASC, UAttributeSet*& OutAS){
	if (!IsValid(PC)) return nullptr;
	if (auto HUD = Cast<AAuraHUD>(PC->GetHUD()); HUD){
		auto PS = PC->GetPlayerState<AAuraPlayerState>(); check(PS); OutPS = PS;
		auto ASC = PS->GetAbilitySystemComponent(); check(ASC); OutASC = ASC;
		auto AS = PS->GetAttributeSet(); check(AS); OutAS = AS;// AttributeSet
		return HUD;
	}
	return nullptr;
}
