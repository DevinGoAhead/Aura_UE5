// Copyright  By Devin


#include "Character/AuraEnemy.h"
#include "Aura/DebugMacros.h"

AAuraEnemy::AAuraEnemy() {
	auto EnemyMesh = GetMesh();
	// block 表示trace 到就停止
	EnemyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(GCustom_Stencil_Depth);
}

void AAuraEnemy::HighLightSelf() {
	DRAW_DEBUG_SPHERE(this, GetActorLocation());
	GetMesh()->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighLightSelf() {
	DRAW_DEBUG_SPHERE(this, GetActorLocation(), 24, 12, FColor::Red);
	GetMesh()->SetRenderCustomDepth(false);
}
