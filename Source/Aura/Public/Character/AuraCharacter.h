// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	/** begin of ICombatInterface*/
	virtual uint8 GetCharacterLevel() const override;
	/** end of ICombatInterface*/
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
private:

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCameraComponent> CameraView;
};
