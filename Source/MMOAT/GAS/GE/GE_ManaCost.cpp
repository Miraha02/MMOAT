// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_ManaCost.h"

#include "MMOAT/GAS/AttributeSets/CharacterAttributeSet.h"

UGE_ManaCost::UGE_ManaCost()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo ManaCost;
	ManaCost.Attribute = FGameplayAttribute(UCharacterAttributeSet::GetManaAttribute());
	ManaCost.ModifierOp = EGameplayModOp::Additive;

	FSetByCallerFloat CallerMagnitude;
	CallerMagnitude.DataTag = FGameplayTag::RequestGameplayTag(FName("Skill.Mana.Cost"));
	ManaCost.ModifierMagnitude = FGameplayEffectModifierMagnitude(CallerMagnitude);

	Modifiers.Add(ManaCost);

	// Identify this GE as a Cost
	InheritableOwnedTagsContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.Cost.Mana")));

}
