// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RDRangeAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ARDRangeAIController : public AAIController
{
	GENERATED_BODY()

protected:
    	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	
};
