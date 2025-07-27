// Copyright  By Devin


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth(){
	// 这里其实就是类似 AttributeBased > Backing Attribute 里的那几项内容
	InitialDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute(); // 指向类型的指针
	InitialDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target; // Source 或 Target 没区别, 因为自己 Apply to 自己
	InitialDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(InitialDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const{
	// Spec.CapturedSourceTags; // Effect 创建时, 快照保存 创建者的 Tags
	// Spec.CapturedTargetTags; // ApplyEffect 时, 快照保存被Apply 的对象的 Tags

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float InitialValue = 0.f; // VigorValue
	/**Convenience method to get attribute magnitude during a CalculateMagnitude call 
	 * VigorAttribute 的值会写入 VigorValue
	 */
	GetCapturedAttributeMagnitude(InitialDef, Spec, EvaluationParameters, InitialValue); 
	if (InitialValue < 0.f) InitialValue = 0.f;
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject()); // 创建 Effect 的 Object
	check(CombatInterface);
	const auto CharacterLevel = CombatInterface->GetCharacterLevel();
	return 80.f + 2.5f * InitialValue + 10.f * CharacterLevel;
}
