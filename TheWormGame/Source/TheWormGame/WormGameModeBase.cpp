// Fill out your copyright notice in the Description page of Project Settings.


#include "WormGameModeBase.h"
#include "SpermCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void AWormGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    PlayerSperm = Cast<ASpermCharacterBase>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AWormGameModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == PlayerSperm)
    {
        HandleGameOver(false);
        bGameHasEnded = true;
    }
}

void AWormGameModeBase::ActorWon(AActor* WinningActor)
{
    if (WinningActor == PlayerSperm)
    {
        HandleGameOver(true);
        bGameHasEnded = true;
        return;
    }

    HandleGameOver(false, true);
    bGameHasEnded = true;
}

void AWormGameModeBase::HandleGameOver(bool PlayerWon, bool bIsTimeout)
{
    if (bGameHasEnded) return;

    GameOver(PlayerWon, bIsTimeout);
}
