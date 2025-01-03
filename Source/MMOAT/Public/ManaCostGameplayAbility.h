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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana Cost")
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float Cooldown;
};
