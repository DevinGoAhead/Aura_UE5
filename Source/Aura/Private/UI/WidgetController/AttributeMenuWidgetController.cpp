// Copyright  By Devin


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem//Data/AuraAttributeDataAsset.h"

#include "AbilitySystem/AuraAttributeSet.h"

// AAuraHUD::InitOverlay 中调用
void UAttributeMenuWidgetController::BroadcastInitValue(){
	Super::BroadcastInitValue();
	const auto AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	checkf(AttributeDataAsset, TEXT("AttributeDataAsset is null"));
	
	for (const auto& [Tag, GetAttributeName] : AuraAS->TagToAttribute){
		auto AuraAttributeInfo = AttributeDataAsset->FindAttributeInfoForTag(Tag);
		AuraAttributeInfo.AttributeValue = GetAttributeName().GetNumericValue(AuraAS);
		AttributeInfoDelegate.Broadcast(AuraAttributeInfo);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies(){
	Super::BindCallbacksToDependencies();
}
