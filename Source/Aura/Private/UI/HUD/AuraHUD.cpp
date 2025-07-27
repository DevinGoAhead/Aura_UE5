// Copyright  By Devin


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

// 在 AAuraCharacter::InitAbilityActorInfo 中被调用
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) {
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is invalid"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is invalid"));
	if (UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass); UserWidget) {
		OverlayWidget = CastChecked<UAuraUserWidget>(UserWidget); // 创建 Widget

		// 初始化 controller
		const FWidgetControllerParams WCP{PC, PS, ASC, AS};
		if (!OverlayWidgetController) InitOverlayWidgetController(WCP);
		OverlayWidget->SetWidgetController(OverlayWidgetController); // UAuraUserWidget 成员函数, 会同时调用蓝图可实现事件
		if (!AttributeMenuWidgetController) InitAttributeMenuWidgetController(WCP);

		// WidgetController 已初始化完成, 并且也注册到了 Widget 中, 可以广播
		OverlayWidgetController->BroadcastInitValue();
		// AttributeMenuWidget 要在 游戏中单击按钮完成初始化, 因而在这里 Broadcast 没用
		// AttributeMenuWidgetController->BroadcastInitValue(); 
		
		UserWidget->AddToViewport();// 添加到视口
	}
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCP) {
	if (OverlayWidgetController) return OverlayWidgetController;
	InitOverlayWidgetController(WCP); return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCP){
	if (AttributeMenuWidgetController) return AttributeMenuWidgetController;
	InitAttributeMenuWidgetController(WCP); return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlayWidgetController(const FWidgetControllerParams& WCP) {
	if (OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass); OverlayWidgetController) {
		OverlayWidgetController->InitWidgetController(WCP);
		OverlayWidgetController->BindCallbacksToDependencies(); // 我感觉在  InitOverlay 中调用更合理啊
	}
	// 通常不会到这里
	checkf(OverlayWidgetController, TEXT("OverlayWidgetController is null"));
}

void AAuraHUD::InitAttributeMenuWidgetController(const FWidgetControllerParams& WCP){
	if (AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass); AttributeMenuWidgetController) {
		AttributeMenuWidgetController->InitWidgetController(WCP);
		AttributeMenuWidgetController->BindCallbacksToDependencies(); 
	}
	// 通常不会到这里
	checkf(AttributeMenuWidgetController, TEXT("AttributeMenuWidgetController is null"));
}
