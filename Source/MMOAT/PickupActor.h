// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Character/Controller/MMOPlayerController.h"
#include "PickupActor.generated.h"

UCLASS()
class MMOAT_API APickupActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


    UPROPERTY()
    TSet<AActor*> OverlappingActors;

    void NotifyActorsBeforeDestroy();

public:
    virtual bool Interact_Implementation(AActor* Interactor) override;
    

    // Déclare la fonction Server pour la destruction
    UFUNCTION(BlueprintCallable,Server,Reliable)
    void Server_Destroy();  // Appelée par les clients pour initier la destruction


    // Retirer l'objet de la liste des objets interactables du joueur
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void RemoveFromPlayerInteractables(AActor* Interactor);

};

