// Copyright  By Devin


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include <type_traits>

// Sets default values
AAuraEffectActor::AAuraEffectActor() {
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
}

void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<class UGameplayEffect> GameEffectClass){
	checkf(GameEffectClass, TEXT("GameEffectClass is invalid"));
	if (const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor); TargetASC) {
		auto GEContextHandle = TargetASC->MakeEffectContext();
		GEContextHandle.AddSourceObject(this);// Sets the object this effect was created from
		auto GESHandle = TargetASC->MakeOutgoingSpec(GameEffectClass, ActorLevel, GEContextHandle);
		//auto ActiveGameEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GESHandle.Data.Get());
		auto ActiveGameEffectHandle = TargetASC->ApplyGameplayEffectSpecToTarget(*GESHandle.Data.Get(), TargetASC);
		if (GESHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite){
			ActiveEffectHandles.Add(ActiveGameEffectHandle, TargetASC);
		}
		else {
			Destroy();
		}
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor) {
	if (InstantGameEffectClass && InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		ApplyEffectToTarget(TargetActor, InstantGameEffectClass);
	}
	if (DurationGameEffectClass && DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		ApplyEffectToTarget(TargetActor, DurationGameEffectClass);
	}
	if (InfiniteGameEffectClass && InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		ApplyEffectToTarget(TargetActor, InfiniteGameEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor) {
	if (InstantGameEffectClass && InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, InstantGameEffectClass);
	}
	if (DurationGameEffectClass && DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, DurationGameEffectClass);
	}
	if (InfiniteGameEffectClass && InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, InfiniteGameEffectClass);
	}
	if (InfiniteGameEffectClass && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
		if (const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor); TargetASC) {
			// 迭代器直接做 bool 使用
			// 会崩溃
			// for (auto Iter = ActiveEffectHandles.CreateIterator(); Iter;){
			// 	if (Iter.Value() == TargetASC) {
			// 		TargetASC->RemoveActiveGameplayEffect(Iter.Key());
			// 		Iter.RemoveCurrent();
			// 	}
			// 	else {
			// 		++Iter;
			// 	}
			// }
			TArray<FActiveGameplayEffectHandle> EffectHandlesRm;
			for (auto& [Handle, ASC] : ActiveEffectHandles){
				if (ASC == TargetASC) {
					TargetASC->RemoveActiveGameplayEffect(Handle);
					EffectHandlesRm.Add(Handle);
				}
			}
			for (const auto& Handle : EffectHandlesRm){
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}

void AAuraEffectActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

