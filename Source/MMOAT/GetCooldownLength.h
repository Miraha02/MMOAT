// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GetCooldownLength.generated.h"

/**
 * 
 */
UCLASS()
class MMOAT_API UGetCooldownLength : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
