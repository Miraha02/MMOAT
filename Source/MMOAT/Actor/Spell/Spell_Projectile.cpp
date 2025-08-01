// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MMOAT/Err.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASpell_Projectile::ASpell_Projectile()
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
void ASpell_Projectile::BeginPlay()
{
	Super::BeginPlay();

	IS_NOT_NULL(ParticleSystem->Template, "ParticleSystem->Template has not been initialized in BP_Spell_Projectile Subclasses");
	IS_NOT_NULL(CollisionComponent, "Collision COmponent Should be settled in BP (in Construct script for example)");
	IS_NOT_NULL(GameplayEffectClass, "GameplayEffectClass has not been filled in Spell_Projectile SubClasses Archetype");

	CollisionComponent->OnComponentHit.AddDynamic(this, &ASpell_Projectile::OnHit);
}

// Called every frame
void ASpell_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell_Projectile::OnSpellImpact_Implementation(AActor* Target)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Target Found"));
		return;
	}
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!TargetASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target does not have an AbilitySystemComponent"));
		return;
	}

	// Setup Effect using Set By Caller
	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContext);
	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Skill.Damage")), Damage);
		TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
		
		UE_LOG(LogTemp, Display, TEXT("GameplayEffect applied with Damage: %f"), Damage);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Invalid GameplayEffectSpecHandle"));
}

void ASpell_Projectile::SetCollisionComponent(UShapeComponent* NewCollisionComponent)
{
	if (NewCollisionComponent)
	{
		CollisionComponent = NewCollisionComponent;
	}
}

void ASpell_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	OnSpellImpact(OtherActor);
}
