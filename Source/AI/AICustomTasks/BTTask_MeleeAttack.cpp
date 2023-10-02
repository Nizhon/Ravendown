// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "AIController.h"
#include "game/Entities/Enemies/RDEnemy.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = "MeleeAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTask_MeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if(enemy->currentHealth <= 0)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	}
	
	attackTimer += DeltaSeconds;

	if(attackTimer >= 0.2f)
	{
		enemy->UseBasicAttack();
		attackTimer = 0;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
