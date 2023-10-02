// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RapidFire.h"

#include "AIController.h"
#include "game/Entities/Enemies/RDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RapidFire::UBTTask_RapidFire()
{
	NodeName = "RapidFire";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RapidFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_RapidFire::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	const float yaw = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), PlayerPawn->GetActorLocation()).Yaw;

	FRotator currentRot = enemy->GetActorRotation();
	currentRot.Yaw = yaw;
	
	enemy->SetActorRotation(currentRot);
	
	Cooldown += DeltaSeconds;
	if(Cooldown >= 1)
	{
		enemy->UseRapidFireAttack();
		Cooldown = 0;
		attackCount++;
	}

	if(attackCount >= 3)
	{
		attackCount = 0;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}

//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Fireball Used");
}
