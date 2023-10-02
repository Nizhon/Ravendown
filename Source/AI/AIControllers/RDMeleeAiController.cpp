// Fill out your copyright notice in the Description page of Project Settings.


#include "RDMeleeAiController.h"
#include "Kismet/GameplayStatics.h"

#include "BehaviorTree/BlackboardComponent.h"

void ARDMeleeAiController::BeginPlay()
{
	Super::BeginPlay();
	
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}
