// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BP_Spell_Projectile.generated.h"

UCLASS()
class MMOAT_API ABP_Spell_Projectile : public AActor
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(EditDefaultsOnly, Category = Particle)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;

public:

private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ABP_Spell_Projectile();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
