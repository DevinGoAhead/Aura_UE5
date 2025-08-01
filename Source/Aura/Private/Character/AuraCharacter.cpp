// Copyright  By Devin


#include "Character/AuraCharacter.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SprintArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400;
	SpringArm->bEnableCameraLag = true; // 摄像机滞后目标, 更顺滑

	// 不继承父组件的旋转
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	
	CameraView = CreateDefaultSubobject<UCameraComponent>(FName("CameraView"));
	CameraView->SetupAttachment(SpringArm);
	CameraView->bUsePawnControlRotation = false; // controller 的旋转不影响相机

	// 不使用 controller 的旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	// 例如, 当按下 d, 角色会向右旋转
	const auto TempV = GetCharacterMovement();
	TempV->bConstrainToPlane = true;
	TempV->bSnapToPlaneAtStart = true;
	TempV->bOrientRotationToMovement = true;
	TempV->RotationRate = FRotator(0, 400.f, 0);
}
// 在 APlayerController::OnPossess 被调用(引擎调用)
void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	InitAbilityActorInfo(); // for server
}

void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	InitAbilityActorInfo(); // for client
}

uint8 AAuraCharacter::GetCharacterLevel() const{
	auto AuraPlayerState = GetPlayerState<AAuraPlayerState>(); // APawn::
	checkf (IsValid(AuraPlayerState), TEXT("PlayerState is InValid in %s"),*GetName());
	return AuraPlayerState->GetCharacterLevel();
}

void AAuraCharacter::BeginPlay() {
	Super::BeginPlay();
}

// 在 AAuraCharacter::PossessedBy 中被调用
void AAuraCharacter::InitAbilityActorInfo() {
	if (const auto AuraPlayerState = GetPlayerState<AAuraPlayerState>(); AuraPlayerState){
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();
		AbilitySystemComponent->InitAbilityActorInfo( AuraPlayerState, this);
		Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); // AbilityActorInfoSet 非多态, 调用与指针类型有关 
		if (const auto PlayerController = GetController<AAuraPlayerController>(); PlayerController) {
			if (const auto HUD = Cast<AAuraHUD>(PlayerController->GetHUD()); HUD) {
				HUD->InitOverlay(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			}
		}
		InitialDefaultAttribute();
	}
}
