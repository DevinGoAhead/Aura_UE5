// Copyright  By Devin


#include "Player/AuraPlayerController.h"
#include "Character/AuraEnemy.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"


AAuraPlayerController::AAuraPlayerController() {
	// 当服务器上的实体变化时, 服务器上的变化会复制或发送到所有连接的客户端
	// 本质就是响应服务器上的数据更新
	// 因而玩家控制器要被指定为一个可复制的实体
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (AuraContext && Subsystem) {
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
}

void AAuraPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);
	UpdateActorUnderCursor();
	UpdateActorHighlight();
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const struct FInputActionValue& InputActionValue) {
	const auto InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator ControlYawRotation(0.f, GetControlRotation().Yaw, 0.0f);
	const auto ControlForwardDirection = FRotationMatrix(ControlYawRotation).GetUnitAxis(EAxis::X);
	const auto ControlRightDirection = FRotationMatrix(ControlYawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlPawn = GetPawn<APawn>()) {
		ControlPawn->AddMovementInput(ControlForwardDirection, InputAxisVector.Y);
		ControlPawn->AddMovementInput(ControlRightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::UpdateActorUnderCursor() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) {
		LastActor = CurActor;
		CurActor = nullptr;
	}
	else {
		LastActor = CurActor;
        CurActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	}
}

void AAuraPlayerController::UpdateActorHighlight() const {
	//LastActor == nullptr && CurActor == nullptr, do nothing
	if (!LastActor && CurActor) {
		CurActor->HighLightSelf();
	}
	else if (LastActor) {
		// CurActor && CurActor == LastActor, do nothing
		if (CurActor && CurActor != LastActor) {
			CurActor->HighLightSelf();
			LastActor->UnHighLightSelf();
		}
		else if (!CurActor){
			LastActor->UnHighLightSelf();
		}
	}
}

