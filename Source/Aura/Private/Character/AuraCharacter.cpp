// Copyright  By Devin


#include "Character/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	auto TempV = GetCharacterMovement();
	TempV->bConstrainToPlane = true;
	TempV->bSnapToPlaneAtStart = true;
	TempV->bOrientRotationToMovement = true;
	TempV->RotationRate = FRotator(0, 400.f, 0);
}
