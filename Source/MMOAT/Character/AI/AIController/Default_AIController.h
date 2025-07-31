// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Default_AIController.generated.h"

UCLASS()
class MMOAT_API ADefault_AIController : public AAIController
{
	GENERATED_BODY()

private:

	UBlackboardComponent* BlackboardComp;

protected:
	
public:

private:

	void SetNearestPlayerInBlackboard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Sets default values for this actor's properties
	ADefault_AIController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
