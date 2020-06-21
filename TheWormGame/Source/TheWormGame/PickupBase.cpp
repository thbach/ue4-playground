// Copywrite TB 2020


#include "PickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "SpermCharacterBase.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	SetRootComponent(PickupMesh);

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &APickupBase::ActorBeginOverlap);
}

void APickupBase::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!SpermClass) return;

	if (OtherActor->GetClass() == SpermClass)
	{
		Cast<ASpermCharacterBase>(OtherActor)->HandleHealthHit(Damage);
		Destroy();
	}
}

