// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTTask_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_ChargeAttack();
	
protected:
	
	//FVector chargePosition;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float chargeLength;

	bool validPoint;
};
