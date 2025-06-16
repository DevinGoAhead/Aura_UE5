// Copyright  By Devin


#include "Actor/AuraEffectActor.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;
	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(RootComponent);
}

void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult) {
	if (const auto ASCInterface = Cast<IAbilitySystemInterface>(OtherActor)) {
		// ASCInterface 指向 AActor*,  AActor* 指向AuraCharacter,  AuraCharacter 的基类 AuraCharacterBase 中定义了 GetAbilitySystemComponent
		const auto AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAttributeSet::StaticClass()));
		auto TempV = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		TempV->SetHealth(TempV->GetHealth() * 1.5);
		TempV->SetMana(TempV->GetMana() * 1.5);
	}
	Destroy();
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex) {
}

void AAuraEffectActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

