// Fill out your copyright notice in the Description page of Project Settings.


#include "GetCooldownLength.h"

#include "ManaCostGameplayAbility.h"

float UGetCooldownLength::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {

	const UManaCostGameplayAbility* Ability = Cast<UManaCostGameplayAbility>(Spec.GetContext().GetAbility());

	if (!Ability) {
		return 0.f;
	}

	return Ability->Cooldown;

}
