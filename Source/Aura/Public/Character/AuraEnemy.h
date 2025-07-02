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
	virtual void HighLightSelf() override;
	virtual void UnHighLightSelf() override;
protected:
	virtual void InitAbilityActorInfo() override;
};
