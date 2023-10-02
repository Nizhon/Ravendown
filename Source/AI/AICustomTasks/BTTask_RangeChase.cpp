// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RangeChase.h"

#include "AIController.h"
#include "game/Entities/Enemies/RDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RangeChase::UBTTask_RangeChase()
{
	NodeName = "ChasePlayer";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RangeChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_RangeChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if(enemy->currentHealth <= 0)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	}
	
	Distance = (AIPawn->GetActorLocation() - PlayerPawn->GetActorLocation()).Length();

	FVector AIPos = AIPawn->GetActorLocation();

	AIPos.Z = 38.5f;

	AIPawn->SetActorLocation(AIPos);
	
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString::SanitizeFloat(Distance));

	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		if(Distance > enemyRange)
		{
			OwnerComp.GetAIOwner()->MoveToActor(PlayerPawn);
			movementVelocity = AIPawn->GetVelocity();
			if(movementVelocity.Length() > 0.01f)
			{
				movementRotation.Yaw = movementVelocity.Rotation().Yaw;
				movementRotation = FMath::RInterpTo(AIPawn->GetActorRotation(), movementRotation, DeltaSeconds, rotationSpeed);
				AIPawn->SetActorRotation(movementRotation);
			}
		}
		else
		{
			OwnerComp.GetAIOwner()->StopMovement();
		
			const float yaw = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), PlayerPawn->GetActorLocation()).Yaw;

			FRotator currentRot = AIPawn->GetActorRotation();
			currentRot.Yaw = yaw;

			currentRot = FMath::RInterpTo(AIPawn->GetActorRotation(), currentRot, DeltaSeconds, rotationSpeed);
			
			AIPawn->SetActorRotation(currentRot);
		
			FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		}
	}
	else
	{
		// FVector newLocation = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).Cross(FVector::UpVector);
		
		OwnerComp.GetAIOwner()->MoveToActor(PlayerPawn);
		movementVelocity = AIPawn->GetVelocity();
		if(movementVelocity.Length() > 0.01f)
		{
			movementRotation.Yaw = movementVelocity.Rotation().Yaw;
			movementRotation = FMath::RInterpTo(AIPawn->GetActorRotation(), movementRotation, DeltaSeconds, rotationSpeed);
			AIPawn->SetActorRotation(movementRotation);
		}
	}
}
