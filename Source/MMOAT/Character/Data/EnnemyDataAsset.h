// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MMOAT_API UEnnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data", meta=(AllowPrivateAccess=true))
	float MaxHealth = 1.0f;

public:
	float GetMaxHealth() const;
	float GetDamage() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data", meta=(AllowPrivateAccess=true))
	float Damage = 1.0f;
	
public:

	
};
