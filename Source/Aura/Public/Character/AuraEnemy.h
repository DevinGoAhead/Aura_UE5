// Copyright  By Devin

#pragma once

constexpr  uint8 GCustom_Stencil_Depth = 250;
#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
	virtual void BeginPlay() override;
	/** begin of IEnemyInterface */
	virtual void HighLightSelf() override;
	virtual void UnHighLightSelf() override;
	/** end of IEnemyInterface */

	/** begin of ICombatInterface*/
	virtual uint8 GetCharacterLevel() const override;
	/** end of ICombatInterface*/
protected:
	virtual void InitAbilityActorInfo() override;
private:
	UPROPERTY(EditAnywhere)
	uint8 Level = 1; // 等级
};
