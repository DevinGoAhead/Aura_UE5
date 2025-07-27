// Copyright  By Devin


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags  FAuraGameplayTags::GameplayTagsInstance; // 声明

const FAuraGameplayTags& FAuraGameplayTags::Get(){
	//static FAuraGameplayTags GameplayTagsInstance;
	return GameplayTagsInstance;
}

void FAuraGameplayTags::InitialNativeGameplayTags(){
	/* 
	 ** UGameplayTagsManager::Get() // Returns the global UGameplayTagsManager manager
	 ** AddNativeGameplayTag, 注册 / 添加 一个 Tag
	 */
    auto &GameplayTagsManager = UGameplayTagsManager::Get();

    // Native Tag of Primary Attribute 
    GameplayTagsInstance.Attributes_Primary_Vigor = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Vigor"),
        FString("Increases Health"));
    GameplayTagsInstance.Attributes_Primary_Strength = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Strength"),
        FString("Increases physical damage"));
    GameplayTagsInstance.Attributes_Primary_Resilience = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Resilience"),
        FString("Increases Armor and Armor Penetration"));
    GameplayTagsInstance.Attributes_Primary_Intelligence = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Intelligence"),
        FString("Increases magical damage"));

    // Native Tag of Secondary Attribute 
	GameplayTagsInstance.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance"));
	GameplayTagsInstance.Attributes_Secondary_ArmorPenetration = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.ArmorPenetration"),
        FString("Ignores percentage of enemy Armor, increases Crit Hit Chance")
    );
    GameplayTagsInstance.Attributes_Secondary_BlockChance = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.BlockChance"),
        FString("Chance to cut incoming damage in half")
    );
    GameplayTagsInstance.Attributes_Secondary_CriticalHitChance = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitChance"),
        FString("Chance to double damage plus critical hit bonus")
    );
    GameplayTagsInstance.Attributes_Secondary_CriticalHitDamage = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitDamage"),
        FString("Bonus damage added when a critical hit is scored")
    );
    GameplayTagsInstance.Attributes_Secondary_CriticalHitResistance = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitResistance"),
        FString("Reduces critical hit chance of attacking enemies")
    );
    GameplayTagsInstance.Attributes_Secondary_HealthRegeneration = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.HealthRegeneration"),
        FString("Amount of Health regenerated every 1 second")
    );
    GameplayTagsInstance.Attributes_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.ManaRegeneration"),
        FString("Amount of Mana regenerated every 1 second")
    );
    GameplayTagsInstance.Attributes_Secondary_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxHealth"),
        FString("Maximum amount of Health obtainable")
    );
   GameplayTagsInstance. Attributes_Secondary_MaxMana = GameplayTagsManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxMana"),
        FString("Maximum amount of Mana obtainable")
    );
}
