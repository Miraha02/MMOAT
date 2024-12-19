// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ManaCostGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MMOAT_API UManaCostGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float Cost;

	UPROPERTY(EditDefaultsOnly)
	float Cooldown;
};
