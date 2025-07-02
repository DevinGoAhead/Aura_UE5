// Copyright  By Devin


#include "UI/Widget/AuraUserWidget.h"

// 在 AAuraHUD::InitOverlay 中被调用
void UAuraUserWidget::SetWidgetController(UObject* InWidgetController) {
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
