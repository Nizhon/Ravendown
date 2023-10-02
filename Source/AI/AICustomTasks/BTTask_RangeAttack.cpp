// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RangeAttack.h"

#include "AIController.h"
#include "game/Entities/Enemies/RDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RangeAttack::UBTTask_RangeAttack()
{
	NodeName = "RangeAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTask_RangeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(enemy->currentHealth <= 0)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	}
	
	const float yaw = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), playerPawn->GetActorLocation()).Yaw;
    
    FRotator currentRot = enemy->GetActorRotation();
    currentRot.Yaw = yaw;

	enemy->SetActorRotation(currentRot);
	
	attackTimer += DeltaSeconds;
	
	if(attackTimer >= 0.48f)
	{
		enemy->UseBasicAttack();
	}
}