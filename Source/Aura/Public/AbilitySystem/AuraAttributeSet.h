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
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
protected:
	// 这是由引擎调用的
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties* EffectProp);
	static void CompleteEffectPropertiesFromInfo(const FGameplayAbilityActorInfo* ActorInfo, AController*& Controller, AActor*& Actor, ACharacter*& Character);
public:
	// 可同步, 并且同步函数为 OnRep_Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "VitalAttributes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "VitalAttributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "VitalAttributes")
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "VitalAttributes")
	FGameplayAttributeData MaxMana;
};
