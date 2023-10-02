// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RangeChase.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTTask_RangeChase : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RangeChase();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float enemyRange = 50;
	float Distance;
	float rotationSpeed = 10;
	FVector movementVelocity;
	FRotator movementRotation;
};
