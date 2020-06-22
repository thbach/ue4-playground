// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpermCharacterBase.generated.h"

class USceneComponent;
class AWormGameModeBase;

UCLASS()
class THEWORMGAME_API ASpermCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ASpermCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleHealthHit(float Damage);
	void HandleSpeedHit(float SpeedModifier);

	UFUNCTION(BlueprintPure)
	bool IsDead() const { return Health <= 0; }

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const { return Health / MaxHealth; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	// Components


	// Config
	UPROPERTY(VisibleAnywhere)
	AWormGameModeBase* GameModeRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DefaultXDrift = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float XSpeed = 0.4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float DefaultHealthDrainRate = 2;

	UPROPERTY(VisibleAnywhere)
	float XDrift;
	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(VisibleAnywhere)
	float HealthDrainRate;

	void DriftForward(float DeltaTime);
	void DrainHealth(float DeltaTime);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void HandleDeath();

};
