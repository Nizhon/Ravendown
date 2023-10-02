// Fill out your copyright notice in the Description page of Project Settings.


#include "RDRangeAIController.h"
#include "Kismet/GameplayStatics.h"

void ARDRangeAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}
