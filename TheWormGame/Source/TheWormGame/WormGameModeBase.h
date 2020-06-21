// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WormGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class THEWORMGAME_API AWormGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void ActorDied(AActor* DeadActor);

};
