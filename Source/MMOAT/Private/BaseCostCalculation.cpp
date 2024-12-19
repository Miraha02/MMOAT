// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCostCalculation.h"
#include "ManaCostGameplayAbility.h"

float UBaseCostCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {

	const UManaCostGameplayAbility* Ability= Cast<UManaCostGameplayAbility>(Spec.GetContext().GetAbility());

	if (!Ability) {
		return 0.f;
	}

	return Ability->Cost;

}
