// Copyright  By Devin

#pragma once

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) /*反射, 必须有*/\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)
	
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

struct FAuraGameplayTags;
class ACharacter;

USTRUCT()
struct FEffectProperties {
	GENERATED_BODY()
	FEffectProperties() = default;
	
	UPROPERTY()
	UAbilitySystemComponent* InstigatorACS = nullptr;
	UPROPERTY()
	AController* InstigatorController = nullptr; // 只有当AvatarActor 指向的对象为APawn 系时, 才不为nullptr
	UPROPERTY()
	AActor* InstigatorAvatarActor = nullptr;
	UPROPERTY()
	ACharacter* InstigatorAvatarCharacter = nullptr; // 只有当AvatarActor指向的类型为 ACharacter 才不为nullptr

	UPROPERTY()
	UAbilitySystemComponent* TargetACS = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr; 
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	ACharacter* TargetAvatarCharacter = nullptr;
};

// FGameplayAttribute(): 无参, 返回值为 FGameplayAttribute 的函数类型(非函数指针)
// - FFuncPtr 是函数类型 FGameplayAttribute() 对应的函数指针类型
using GetAttributeTypeFuncPtr = TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// Vital Attributes
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	// Primary Attributes
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	// Secondary Attributes
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
//protected:
private:
	// 这是由引擎调用的

	// Vital Attributes
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	// Primary Attributes
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	// Secondary Attributes
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties* EffectProp);
	static void CompleteEffectPropertiesFromInfo(const FGameplayAbilityActorInfo* ActorInfo, AController*& Controller, AActor*& Actor, ACharacter*& Character);

public:
	// Vital Attributes
	// 可同步, 并且同步函数为 OnRep_...
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "VitalAttributes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "VitalAttributes")
	FGameplayAttributeData Mana;
	
	// Primary Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "PrimaryAttributes")
	FGameplayAttributeData Strength;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "PrimaryAttributes")
	FGameplayAttributeData Intelligence;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "PrimaryAttributes")
	FGameplayAttributeData Resilience;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "PrimaryAttributes")
	FGameplayAttributeData Vigor;

	// Secondary Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "SecondaryAttributes")
	FGameplayAttributeData Armor;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "SecondaryAttributes")
	FGameplayAttributeData ArmorPenetration;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "SecondaryAttributes")
	FGameplayAttributeData BlockChance;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "SecondaryAttributes")
	FGameplayAttributeData CriticalHitChance;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "SecondaryAttributes")
	FGameplayAttributeData CriticalHitDamage;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "SecondaryAttributes")
	FGameplayAttributeData CriticalHitResistance;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "SecondaryAttributes")
	FGameplayAttributeData HealthRegeneration;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "SecondaryAttributes")
	FGameplayAttributeData ManaRegeneration;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "SecondaryAttributes")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "SecondaryAttributes")
	FGameplayAttributeData MaxMana;
public:
	TMap<FGameplayTag, GetAttributeTypeFuncPtr> TagToAttribute;
};
