// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Test_TakeDamage.h"

#include "MMOAT/GAS/AttributeSets/CharacterAttributeSet.h"

UGE_Test_TakeDamage::UGE_Test_TakeDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Crée le modificateur de dégâts
	FGameplayModifierInfo Modifier;
	Modifier.Attribute = UCharacterAttributeSet::GetHealthAttribute();
	Modifier.ModifierOp = EGameplayModOp::Additive;
	Modifier.ModifierMagnitude = FScalableFloat(-1.5);

	Modifiers.Add(Modifier);
}
