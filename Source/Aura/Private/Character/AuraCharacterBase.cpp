// Copyright  By Devin


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
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

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& AttributeGEClass, float Level) const{
	check(IsValid(AbilitySystemComponent) && IsValid(AttributeGEClass));
	auto GEContextHandle = AbilitySystemComponent->MakeEffectContext();
	GEContextHandle.AddSourceObject(this); // Set Object that this Effect was created from
	const auto GESpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AttributeGEClass, 1.f, GEContextHandle);
	//AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GESpec.Data.Get(), AbilitySystemComponent);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get()); // 我感觉这样更合适
}

void AAuraCharacterBase::InitialDefaultAttribute() const{
	ApplyEffectToSelf(PrimaryAttributeGEClass, 1.f);
	ApplyEffectToSelf(SecondaryAttributeGEClass, 1.f);
	ApplyEffectToSelf(VitalAttributeGEClass, 1.f);
}

void AAuraCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

