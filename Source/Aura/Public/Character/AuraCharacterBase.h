// Copyright  By Devin

#pragma once

class UAbilitySystemComponent;
class UAttributeSet;
class USkeletalMeshComponent;
class UStaticMeshComponent;

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	inline UAttributeSet* GetAttributeSet() const { return AttributeSet;}

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName WeaponSocket = "WeaponHandSocket";
private:

};
