// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_ManaDefined.h"
#include "MMOAT/Actor/Spell/Spell_Projectile.h"
#include "GA_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MMOAT_API UGA_Projectile : public UGA_ManaDefined
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<ASpell_Projectile> ProjectileClass;
	
public:

private:

	UGA_Projectile();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
public:
	
};
