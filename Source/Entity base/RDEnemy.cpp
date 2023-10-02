// Fill out your copyright notice in the Description page of Project Settings.


#include "RDEnemy.h"

#include "game/Entities/RDPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARDEnemy::ARDEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    invDelay = 0.5f;

    hasTriggered = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->InitCapsuleSize(17,30);
	CapsuleComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CapsuleComponent->SetGenerateOverlapEvents(true);
}

void ARDEnemy::DisableCollision()
{
	CapsuleComponent->SetCollisionObjectType(ECC_GameTraceChannel3);
}

void ARDEnemy::EnableCollision()
{
	CapsuleComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
}

// Called when the game starts or when spawned
void ARDEnemy::BeginPlay()
{
	Super::BeginPlay();
    DisableCollision();
}

// Called every frame
void ARDEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    invDelay -= DeltaTime;

    if (invDelay <= 0 && !hasTriggered)
    {
        hasTriggered = true;
        EnableCollision();
        invDelay = 0.1f;
    }
}

void ARDEnemy::Die()
{
	Super::Die();
	
    if (!EnemyDeathEvent.IsBound())
    {
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARDPlayer::StaticClass(), foundActors);
        ARDPlayer* player = Cast<ARDPlayer>(foundActors[0]);
        player->GainEssence(essenceOnDeath);
    }
    else
    {
        EnemyDeathEvent.Broadcast(essenceOnDeath);
    }
	DetachFromControllerPendingDestroy();
	OnDeath();
}