// Copyright  By Devin


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::InitWidgetController(const FWidgetControllerParams& WCP) {
	PlayerController = WCP.PlayerController;
	PlayerState = WCP.PlayerState;
	AbilitySystemComponent = WCP.AbilitySystemComponent;
	AttributeSet = WCP.AttributeSet;
}

void UAuraWidgetController::BroadcastInitValue() {
}

void UAuraWidgetController::BindCallbacksToDependencies() {
}
