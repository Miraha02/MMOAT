// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Cooldown.h"

UGE_Cooldown::UGE_Cooldown()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	FSetByCallerFloat SetByCallerData;
	SetByCallerData.DataTag = FGameplayTag::RequestGameplayTag(FName("Skill.Cooldown"));

	DurationMagnitude = FGameplayEffectModifierMagnitude(SetByCallerData);

}
