// Copyright TB 2020


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void APawnTurret::BeginPlay()
{
    Super::BeginPlay();


    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);

}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) return;

    RotateTurret(PlayerPawn->GetActorLocation());
}


void APawnTurret::CheckFireCondition()
{
    if (!PlayerPawn || !PlayerPawn->GetPlayerAlive()) return;

    if (ReturnDistanceToPlayer() > FireRange) return;

    Fire();
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if (!PlayerPawn) return 0.0f;

    float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
    return Distance;
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}