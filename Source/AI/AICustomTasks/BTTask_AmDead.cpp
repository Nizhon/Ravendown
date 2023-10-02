// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AmDead.h"

#include "AIController.h"
#include "game/Entities/Enemies/RDEnemy.h"

UBTTask_AmDead::UBTTask_AmDead()
{
	NodeName = "Dead";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AmDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	
	if(OwnerComp.GetAIOwner() == nullptr || enemy->currentHealth > 0)
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTask_AmDead::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	killTime += DeltaSeconds;

	if(killTime >= 10.0f)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
