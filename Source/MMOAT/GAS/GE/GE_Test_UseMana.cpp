// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Test_UseMana.h"

#include "MMOAT/GAS/AttributeSets/CharacterAttributeSet.h"

UGE_Test_UseMana::UGE_Test_UseMana()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Crée le modificateur de dégâts
	FGameplayModifierInfo Modifier;
	Modifier.Attribute = UCharacterAttributeSet::GetManaAttribute();
	Modifier.ModifierOp = EGameplayModOp::Additive;
	Modifier.ModifierMagnitude = FScalableFloat(-1.5);

	Modifiers.Add(Modifier);
}
