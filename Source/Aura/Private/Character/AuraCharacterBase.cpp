// Copyright  By Devin


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase() {
	PrimaryActorTick.bCanEverTick = true;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
}
void AAuraCharacterBase::BeginPlay() {
	Super::BeginPlay();
	
}

void AAuraCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

