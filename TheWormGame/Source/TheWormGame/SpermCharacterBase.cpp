// Copywrite TB 2020


#include "SpermCharacterBase.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/SceneComponent.h"

// Sets default values
ASpermCharacterBase::ASpermCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpermCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	XDrift = DefaultXDrift;

}

// Called every frame
void ASpermCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Constant dift
	DriftForward();
	Wiggle();

}

// Called to bind functionality to input
void ASpermCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASpermCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASpermCharacterBase::MoveRight);
}

void ASpermCharacterBase::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * XSpeed);
}

void ASpermCharacterBase::DriftForward()
{
	AddActorLocalOffset(GetActorForwardVector() * XDrift * GetWorld()->GetDeltaSeconds(), true);
}

void ASpermCharacterBase::Wiggle()
{
	// AddActorLocalRotation();
}

void ASpermCharacterBase::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASpermCharacterBase::HandleHealthHit(float Damage)
{
	if (Damage == 0 || Health == 0) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("my Health %f"), Health);
	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Im DEAD"), );
	}

}

void ASpermCharacterBase::HandleSpeedHit(float SpeedModifier)
{
	if (SpeedModifier != 1.0f)
	{
		XDrift *= SpeedModifier;
	}
	else
	{
		XDrift = DefaultXDrift;
	}
}

void ASpermCharacterBase::HandleDeath()
{
	// TODO
}

