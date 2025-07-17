// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MMOATCharacterDataTable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MMOAT_API UMMOATCharacterDataTable : public UDataTable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data", meta=(AllowPrivateAccess=true))
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data", meta=(AllowPrivateAccess=true))
	float MaxMana = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data", meta=(AllowPrivateAccess=true))
	float HealthRegen = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data", meta=(AllowPrivateAccess=true))
	float ManaRegen = 1.0f;

public:
	float GetMaxHealth() const;
	float GetMaxMana() const;
	float GetHealthRegen() const;
	float GetManaRegen() const;

inline float UMMOATCharacterDataTable::GetMaxHealth() const
{
	return MaxHealth;
}

inline float UMMOATCharacterDataTable::GetMaxMana() const
{
	return MaxMana;
}

inline float UMMOATCharacterDataTable::GetHealthRegen() const
{
	return HealthRegen;
}

inline float UMMOATCharacterDataTable::GetManaRegen() const
{
	return ManaRegen;
}

};