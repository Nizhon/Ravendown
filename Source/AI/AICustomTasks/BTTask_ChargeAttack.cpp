// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChargeAttack.h"

#include "AIController.h"
#include "BTTask_MeleeChase.h"
#include "game/Entities/Enemies/RDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ChargeAttack::UBTTask_ChargeAttack()
{
	NodeName = "ChargeAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	
	FVector chargePosition = enemy->GetActorLocation();
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	float distance = (enemy->GetActorLocation() - playerPawn->GetActorLocation()).Length();
	chargePosition += enemy->GetActorForwardVector() * (distance + chargeLength);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("ChargePosition"),chargePosition);

	FNavLocation discard;

	UNavigationSystemV1* navMesh = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	
	validPoint = navMesh->GetRandomReachablePointInRadius(chargePosition, 40.0f, discard);
	
	if(!validPoint)
	{
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, "Failed to charge");
		return EBTNodeResult::Failed;
	}
	
	enemy->UseChargeAttack();

	return EBTNodeResult::InProgress;
}

void UBTTask_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ARDEnemy* enemy = Cast<ARDEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if(enemy->currentHealth <= 0)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	}

	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	FVector chargePosition = MyBlackboard->GetValueAsVector("ChargePosition");
	
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	AIPawn->SetActorLocation(FMath::Lerp(AIPawn->GetActorLocation(), chargePosition, DeltaSeconds*10));
	
	if(AIPawn->GetActorLocation().Distance(AIPawn->GetActorLocation(), chargePosition) <= 10)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
