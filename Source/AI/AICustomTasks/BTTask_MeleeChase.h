// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MeleeChase.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTTask_MeleeChase : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_MeleeChase();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float enemyRange = 50;
	float distance;
	float chaseTimer = 0;
	float rotationSpeed = 10;
	FVector movementVelocity;
	FRotator movementRotation;
};
