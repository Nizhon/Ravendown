// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTTask_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_RangeAttack();
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float rotationSpeed = 10;

	UPROPERTY(EditAnywhere)
	float attackTimer = 0;
};