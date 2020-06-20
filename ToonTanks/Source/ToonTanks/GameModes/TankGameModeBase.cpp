// Copyright TB 2020


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TargetTurrets = GetTargetTurretCount();
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        PlayerTank->PawnDestroyed();
        HandleGameOver(false);
        if (PlayerControllerRef) PlayerControllerRef->SetPlayerEnabledState(false);
        return;
    }
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->PawnDestroyed();
        TargetTurrets--;
        if (TargetTurrets <= 0) HandleGameOver(true);
    }
}

void ATankGameModeBase::HandleGameStart()
{
    GameStart();
    if (!PlayerControllerRef) return;

    PlayerControllerRef->SetPlayerEnabledState(false);
    FTimerHandle PlayerEnableHandle;
    FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TSubclassOf<APawnTurret> ClassToFind;
    ClassToFind = APawnTurret::StaticClass();
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);

    return TurretActors.Num();
}
