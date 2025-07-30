// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Spell_Projectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MMOAT/Err.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ABP_Spell_Projectile::ABP_Spell_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ParticleSystem Component
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	IS_NOT_NULL(ParticleSystem, "ParticleSystem Creation Failed !");
	ParticleSystem->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	IS_NOT_NULL(ProjectileMovementComponent, "ProjectileMovementComponent Creation Failed !");
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	// Replicate this actor to everyone
	SetReplicates(true);
	
	
}

// Called when the game starts or when spawned
void ABP_Spell_Projectile::BeginPlay()
{
	Super::BeginPlay();

	IS_NOT_NULL(ParticleSystem->Template, TEXT("ParticleSystem->Template has not been initialized in BP_Spell_Projectile Subclasses");
}

// Called every frame
void ABP_Spell_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABP_Spell_Projectile::OnSpellImpact_Implementation()
{
}