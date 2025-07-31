// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/Default_AIController.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class MMOAT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(EditDefaultsOnly, Category = AIController)
	ADefault_AIController* AIController;
	
public:

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this character's properties
	AAICharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
