// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraAttributeDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly)
	float AttributeValue = 0.f;
};
/**
 * 
 */
UCLASS(Blueprintable)
class AURA_API UAuraAttributeDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& GamePlayTag, bool bLogNotFound = false) const ;
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraAttributeInfo> AttributeInfos;
};
