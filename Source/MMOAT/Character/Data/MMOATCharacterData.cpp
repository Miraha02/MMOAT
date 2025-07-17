// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOATCharacterData.h"

float UMMOATCharacterData::GetMaxHealth() const
{
	return MaxHealth;
}

float UMMOATCharacterData::GetMaxMana() const
{
	return MaxMana;
}

float UMMOATCharacterData::GetHealthRegen() const
{
	return HealthRegen;
}

float UMMOATCharacterData::GetManaRegen() const
{
	return ManaRegen;
}
