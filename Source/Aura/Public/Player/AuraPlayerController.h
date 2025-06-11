// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	void Move(const struct FInputActionValue& InputActionValue);
private:
	void UpdateActorUnderCursor();
	void UpdateActorHighlight() const;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;
	
	class IEnemyInterface* CurActor = nullptr; // 光标 trace 到的当前 actor
	class IEnemyInterface* LastActor = nullptr; // 光标 trace 到的上一个 actor
};
