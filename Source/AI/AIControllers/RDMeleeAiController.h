// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RDMeleeAiController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ARDMeleeAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	// virtual void Tick(float DeltaSeconds) override;
    	
protected:
    	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	
	// FVector MovementVelocity;
	// FRotator MovementRotation;
	
};
