// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AmDead.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTTask_AmDead : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_AmDead();
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	float killTime = 0;
};