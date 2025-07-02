// Copyright  By Devin


#include "Character/AuraCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"


AAuraCharacterBase::AAuraCharacterBase() {
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh(), WeaponSocket);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay() {
	Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilityActorInfo(){
}

void AAuraCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

