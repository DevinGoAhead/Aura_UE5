// Copyright  By Devin


#include "AbilitySystem/Data/AuraAttributeDataAsset.h"

FAuraAttributeInfo UAuraAttributeDataAsset::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
	bool bLogNotFound) const{
	for (const auto& AttributeInfo : AttributeInfos){
		//  "A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
		if (AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag)){
			return AttributeInfo;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Can Not Found AttributeTag [%s] in AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	return FAuraAttributeInfo();
}
