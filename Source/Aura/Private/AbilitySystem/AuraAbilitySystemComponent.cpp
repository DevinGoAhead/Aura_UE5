// Copyright  By Devin


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/DebugMacros.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet(){
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToSelf);
}

void UAuraAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* ASC,
            const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle){
	//ADD_SCREEN_DEBUG(-1, FString("Effect Applied"));
	FGameplayTagContainer TagContainer;
	GESpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
