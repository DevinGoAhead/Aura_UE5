// Copyright  By Devin

#pragma once
#include "Interaction/CombatInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
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
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& AttributeGEClass, float Level) const;
	void InitialDefaultAttribute() const;
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	TSubclassOf<UGameplayEffect> VitalAttributeGEClass;
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	TSubclassOf<UGameplayEffect> PrimaryAttributeGEClass;
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	TSubclassOf<UGameplayEffect> SecondaryAttributeGEClass;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName WeaponSocket = "WeaponHandSocket";
private:
};
