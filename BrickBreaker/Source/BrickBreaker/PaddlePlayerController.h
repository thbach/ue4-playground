// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaddlePlayerController.generated.h"

class ABall;
class APaddle;


UCLASS()
class BRICKBREAKER_API APaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APaddlePlayerController();

	UFUNCTION()
	virtual void SetupInputComponent() override;

	void SpawnNewBall();

protected:
	virtual void BeginPlay() override;

	void MoveHorizontal(float AxisValue);

	void Launch();

private:
	APaddle* MyPawn;
	// ball references

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABall> BallClass;

	ABall* BallActor;

	FVector SpawnLocation = FVector(10.0f, 0.0f, 40.0f);
	FRotator SpawnRotation = FRotator(0.0f);
	FActorSpawnParameters SpawnParams;


};
