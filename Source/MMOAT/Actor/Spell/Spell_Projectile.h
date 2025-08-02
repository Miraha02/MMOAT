// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Spell_Projectile.generated.h"

UCLASS(Abstract, Blueprintable)
class MMOAT_API ASpell_Projectile : public AActor
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(EditDefaultsOnly, Category = Particle)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;

	/** Collider Component That SHould be filled in BP */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	UShapeComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Damage)
	float Damage = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = GE_Tag)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	

public:

private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Spell")
	void OnSpellImpact(AActor* Target);

	virtual void OnSpellImpact_Implementation(AActor* Target);

	/** Setter to Defind Component in Blueprint */
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void SetCollisionComponent(UShapeComponent* NewCollisionComponent);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);


public:
	// Sets default values for this actor's properties
	ASpell_Projectile();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
