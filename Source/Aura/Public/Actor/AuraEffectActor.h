// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
public:
	AAuraEffectActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<class UGameplayEffect> GameEffectClass);
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<class UGameplayEffect> InstantGameEffectClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnBeginOverlap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<class UGameplayEffect> DurationGameEffectClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnBeginOverlap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<class UGameplayEffect> InfiniteGameEffectClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnBeginOverlap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
private:
	UPROPERTY(EditAnywhere, Category = "AppliedEffects")
	float ActorLevel = 1.f;
};
