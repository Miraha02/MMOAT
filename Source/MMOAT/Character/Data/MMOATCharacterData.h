// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MMOATCharacterData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MMOAT_API UMMOATCharacterData : public UDataAsset
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
};
