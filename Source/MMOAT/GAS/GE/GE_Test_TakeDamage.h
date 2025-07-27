// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_Test_TakeDamage.generated.h"

/**
 * @warning THIS CLASS SHOULD NEVER BE USED FOR DEVELOPMENT. IT IS FOR TESTING PURPOSE ONLY !
 */
UCLASS()
class MMOAT_API UGE_Test_TakeDamage : public UGameplayEffect
{
	GENERATED_BODY()

public:
	
	UGE_Test_TakeDamage();
};
