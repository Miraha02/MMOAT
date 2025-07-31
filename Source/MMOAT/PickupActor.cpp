// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Character/MMOATCharacter.h"
#include "GameFramework/Character.h"


#define CAST_TO_MMOATCHARACTER \
auto MMOATCharacter = Cast<AMMOATCharacter>(GetCharacter());\
	if (!MMOATCharacter)\
	{\
		UE_LOG(LogTemp, Error, TEXT("Controlled Character is not a MMOATCharacter"));\
		return;\
	}

#define CAST_TO_MMOATCONTROLLER_FROM_CHARACTER \
auto MMOATCharacter = Cast<AMMOATCharacter>(GetCharacter()); \
    if (!MMOATCharacter) \
    { \
        UE_LOG(LogTemp, Error, TEXT("Actor is not controlled by a valid character")); \
        return; \
    } \
    AController* Controller = MMOATCharacter->GetController(); \
    AMMOPlayerController* MMOATController = Cast<AMMOPlayerController>(Controller); \
    if (!MMOATController) \
    { \
        UE_LOG(LogTemp, Error, TEXT("Failed to cast Controller to MMOATCharacterController")); \
        return; \
    }


// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;  // Permet la réplication de l'acteur

}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void APickupActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		OverlappingActors.Add(OtherActor);

		if (ACharacter* Character = Cast<ACharacter>(OtherActor))
		{
			if (AMMOPlayerController* Controller = Cast<AMMOPlayerController>(Character->GetController()))
			{
				Controller->AddInteractable(this);
			}
		}
	}
}

void APickupActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Remove(OtherActor);

		if (ACharacter* Character = Cast<ACharacter>(OtherActor))
		{
			if (AMMOPlayerController* Controller = Cast<AMMOPlayerController>(Character->GetController()))
			{
				Controller->RemoveInteractable(this);
			}
		}
	}
}

bool APickupActor::Interact_Implementation(AActor* Interactor)
{
	return false; // par défaut, ne rien faire
}

void APickupActor::RemoveFromPlayerInteractables(AActor* Interactor)
{
    // Assurer que l'Interactor est un ACharacter contrôlé
    if (ACharacter* Character = Cast<ACharacter>(Interactor))
    {
        // Assurer que le personnage a bien un contrôleur et retirer l'item de la liste
        AMMOPlayerController* MMOATController = Cast<AMMOPlayerController>(Character->GetController());
        if (MMOATController)
        {
            // Appeler la fonction pour enlever l'objet de la liste des interactables du joueur
            MMOATController->RemoveInteractable(this);
        }
    }
}

void APickupActor::NotifyActorsBeforeDestroy()
{
	for (AActor* Actor : OverlappingActors)
	{
		if (ACharacter* Character = Cast<ACharacter>(Actor))
		{
			if (AMMOPlayerController* Controller = Cast<AMMOPlayerController>(Character->GetController()))
			{
				Controller->RemoveInteractable(this);
			}
		}
	}
	OverlappingActors.Empty();
}


void APickupActor::Server_Destroy_Implementation() {
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup destroy triggered by server"));
		Destroy();
	}
}
