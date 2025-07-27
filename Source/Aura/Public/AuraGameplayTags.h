// Copyright  By Devin

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 单例, 封装所有的 Native Gameplay Tags
 */
struct FAuraGameplayTags
{
public:
	FAuraGameplayTags(const FAuraGameplayTags& OtherAuraGameplayTags) = delete;
	FAuraGameplayTags& operator=(const FAuraGameplayTags& OtherAuraGameplayTags) = delete;
	FAuraGameplayTags() = default;
public:
	static const FAuraGameplayTags& Get();
	static void InitialNativeGameplayTags();
private:
	static FAuraGameplayTags GameplayTagsInstance; // 单例
public:
	// Native Tag of Primary Attribute 
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Intelligence;
	
	// Native Tag of Secondary Attribute 
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxHealth;
};
