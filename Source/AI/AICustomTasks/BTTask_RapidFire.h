// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RapidFire.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTTask_RapidFire : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RapidFire();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float Distance;
	float Cooldown = 0;
	float attackCount = 0;
};
