// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeathComponent.h"
#include "EnnemyDeathComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MMOAT_API UEnnemyDeathComponent : public UDeathComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnnemyDeathComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HandleDeath_Implementation() override;
};
