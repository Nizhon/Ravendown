// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeChase.h"

#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "game/Entities/Enemies/RDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_MeleeChase::UBTTask_MeleeChase()
{
	NodeName = "ChasePlayer";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MeleeChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_MeleeChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if(enemy->currentHealth <= 0)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	}
	
	FVector AIPos = AIPawn->GetActorLocation();

	AIPos.Z = 38.5f;

	AIPawn->SetActorLocation(AIPos);
	
	distance = (AIPawn->GetActorLocation() - playerPawn->GetActorLocation()).Length();
	
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString::SanitizeFloat(Distance));

	if(distance > enemyRange )
	{
		OwnerComp.GetAIOwner()->MoveToActor(playerPawn);
		movementVelocity = AIPawn->GetVelocity();
		if(movementVelocity.Length() > 0.01f)
		{
			movementRotation.Yaw = movementVelocity.Rotation().Yaw;
			movementRotation = FMath::RInterpTo(AIPawn->GetActorRotation(), movementRotation, DeltaSeconds, rotationSpeed);
			AIPawn->SetActorRotation(movementRotation);
		}
		chaseTimer += DeltaSeconds;
		if(chaseTimer >= 3)
		{
			chaseTimer = 0;
			OwnerComp.GetAIOwner()->StopMovement();

			const float yaw = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), playerPawn->GetActorLocation()).Yaw;

			FRotator currentRot = AIPawn->GetActorRotation();
			currentRot.Yaw = yaw;

			currentRot = FMath::RInterpTo(AIPawn->GetActorRotation(), currentRot, DeltaSeconds, rotationSpeed);
			
			AIPawn->SetActorRotation(currentRot);
			
			FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
		}
	}
	else
	{
		OwnerComp.GetAIOwner()->StopMovement();
		
		const float yaw = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), playerPawn->GetActorLocation()).Yaw;

		FRotator currentRot = AIPawn->GetActorRotation();
		currentRot.Yaw = yaw;

		currentRot = FMath::RInterpTo(AIPawn->GetActorRotation(), currentRot, DeltaSeconds, rotationSpeed);
		
		AIPawn->SetActorRotation(currentRot);
		
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
