// Copywrite TB 2020


#include "SpermCharacterBase.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/SceneComponent.h"
#include "WormGameModeBase.h"

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

	GameModeRef = Cast<AWormGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Health = MaxHealth;
	XDrift = DefaultXDrift;
	HealthDrainRate = DefaultHealthDrainRate;

}

// Called every frame
void ASpermCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Constant dift
	DriftForward(DeltaTime);
	DrainHealth(DeltaTime);
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

void ASpermCharacterBase::DriftForward(float DeltaTime)
{
	AddActorLocalOffset(GetActorForwardVector() * XDrift * DeltaTime, true);
}

void ASpermCharacterBase::DrainHealth(float DeltaTime)
{
	Health = FMath::Clamp(Health - HealthDrainRate * DeltaTime , 0.0f, MaxHealth);
	if (Health <= 0) HandleDeath();
}

void ASpermCharacterBase::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASpermCharacterBase::HandleHealthHit(float Damage)
{
	if (Damage == 0 || Health == 0) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	if (Health <= 0)
	{
		HandleDeath();
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
	UE_LOG(LogTemp, Warning, TEXT("Im DEAD"), );
	XDrift = 0;

	if (!GameModeRef) return;

	GameModeRef->ActorDied(this);
}

