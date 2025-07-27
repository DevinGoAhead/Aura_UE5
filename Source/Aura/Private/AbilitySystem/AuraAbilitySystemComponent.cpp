// Copyright  By Devin


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/DebugMacros.h"

//  在 AAuraCharacter::InitAbilityActorInfo() 中被调用
void UAuraAbilitySystemComponent::AbilityActorInfoSet(){
	/*  OnGameplayEffectAppliedDelegateToSelf
	 ** Called on server whenever a GE is applied to self. This includes instant and duration based GEs
	 */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToSelf);
}
// 回调函数
// ApplyToSelf 的 GE 会保存在game effect spec 中
void UAuraAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* ASC,
            const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle) const{
	//ADD_SCREEN_DEBUG(-1, FString("Effect Applied"));
	FGameplayTagContainer TagContainer;
	GESpec.GetAllAssetTags(TagContainer); // ** Appends ** all tags that apply to this gameplay effect spec
	// 在 UOverlayWidgetController::BindCallbacksToDependencies() 中将一个 Lambda 添加到委托列表
	EffectAssetTags.Broadcast(TagContainer); 
}
