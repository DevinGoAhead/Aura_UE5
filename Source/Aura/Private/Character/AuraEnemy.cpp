// Copyright  By Devin


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/DebugMacros.h"

AAuraEnemy::AAuraEnemy() {
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // 仅同步tag, cue
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	const auto EnemyMesh = GetMesh();
	// block 表示trace 到就停止
	EnemyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(GCustom_Stencil_Depth);
}

void AAuraEnemy::BeginPlay() {
	Super::BeginPlay();
}

void AAuraEnemy::HighLightSelf() {
	//DRAW_DEBUG_SPHERE(this, GetActorLocation());
	GetMesh()->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighLightSelf() {
	//DRAW_DEBUG_SPHERE(this, GetActorLocation(), 24, 12, FColor::Red);
	GetMesh()->SetRenderCustomDepth(false);
}

uint8 AAuraEnemy::GetCharacterLevel() const{
	return Level;
}

void AAuraEnemy::InitAbilityActorInfo(){
	Super::InitAbilityActorInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this, this); // Owner == Avatar == This
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); // AbilityActorInfoSet 非多态, 调用与指针类型有关 
}
