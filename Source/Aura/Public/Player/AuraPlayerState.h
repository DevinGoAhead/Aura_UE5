// Copyright  By Devin

#pragma once

class UAbilitySystemComponent;
class UAttributeSet;

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	inline UAttributeSet* GetAttributeSet() const { return AttributeSet;}
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps ) const override;
	FORCEINLINE uint8 GetCharacterLevel() const {return Level;}
protected:
private:
	UFUNCTION()
	void OnRep_Level(const uint8& OldLevel);
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	uint8 Level = 1; // 等级
};
