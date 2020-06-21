// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpermCharacterBase.generated.h"

UCLASS()
class THEWORMGAME_API ASpermCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpermCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void HandleHealthHit(float Damage);
	void HandleSpeedHit(float SpeedModifier);

private:
	// Config
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DefaultXDrift = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float XSpeed = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float XDrift;
	UPROPERTY(VisibleAnywhere)
	float Health;

	void DriftForward(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void HandleDeath();

};
