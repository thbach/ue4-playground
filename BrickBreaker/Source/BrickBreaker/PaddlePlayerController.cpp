// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Paddle.h"
#include "Ball.h"
#include "Engine/World.h"

APaddlePlayerController::APaddlePlayerController()
{

}

void APaddlePlayerController::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> CameraActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

    FViewTargetTransitionParams Params;
    SetViewTarget(CameraActors[0], Params);

    MyPawn = Cast<APaddle>(GetPawn());

    SpawnNewBall();
}

void APaddlePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    EnableInput(this);

    InputComponent->BindAxis("MoveHorizontal", this, &APaddlePlayerController::MoveHorizontal);
    InputComponent->BindAction("Launch", EInputEvent::IE_Pressed, this, &APaddlePlayerController::Launch);
}

void APaddlePlayerController::MoveHorizontal(float AxisValue)
{
    if (MyPawn)
    {
        MyPawn->MoveHorizontal(AxisValue);
    }
}

void APaddlePlayerController::Launch()
{
    if (BallActor)
    {
        BallActor->Launch();
    }
}

void APaddlePlayerController::SpawnNewBall()
{
    if (!BallActor) BallActor = nullptr;

    if (BallClass)
    {
        BallActor = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation, SpawnParams);
    }

}
