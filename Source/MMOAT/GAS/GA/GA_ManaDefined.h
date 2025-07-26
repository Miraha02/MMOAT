// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_ManaDefined.generated.h"

/**
 * 
 */
UCLASS()
class MMOAT_API UGA_ManaDefined : public UGameplayAbility
{
	GENERATED_BODY()

private:

protected:
	/**
	 * The Mana Used to cast the spell
	 */
	UPROPERTY(EditDefaultsOnly, Category = Mana, meta=(AllowPrivateAccess = "true"))
	float ManaCost = 50.0f;

public:

private:

protected:

	UGA_ManaDefined();
	
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

public:

	
	
};
