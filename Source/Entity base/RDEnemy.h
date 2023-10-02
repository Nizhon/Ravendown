// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "game/Entities/RDEntity.h"
#include "Components/CapsuleComponent.h"
#include "RDEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDEnemyDied, float, essenceAmount);

UCLASS(Blueprintable)
class GAME_API ARDEnemy : public ARDEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARDEnemy();
	
	UPROPERTY(BlueprintAssignable)
	FDEnemyDied EnemyDeathEvent;

	UFUNCTION(BlueprintImplementableEvent)
	void UseBasicAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void UseChargeAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void UseRapidFireAttack();

	void DisableCollision();

	void EnableCollision();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Die() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	bool hasTriggered;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Entity")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, Category="Entity")
	float attackRange;
	UPROPERTY(EditAnywhere, Category="Entity")
	float essenceOnDeath;
	float invDelay; 
};
