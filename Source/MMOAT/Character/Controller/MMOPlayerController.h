// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MMOAT/Interactable.h"
#include "GameFramework/PlayerController.h"
#include "MMOPlayerController.generated.h"


class IInteractable;

/**
 * 
 */
UCLASS()
class MMOAT_API AMMOPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMMOPlayerController();

private:
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> StatsWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* StatsRef;

	// Mapping Context & Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input/Spell")
	UInputAction* SpellAction1;

	UPROPERTY(EditDefaultsOnly, Category = "Input/Spell")
	UInputAction* SpellAction2;

	UPROPERTY(EditDefaultsOnly, Category = "Input/Spell")
	UInputAction* SpellAction3;


public:

private:
	/**
	 * Create the Stats Widget if Controller is client
	 */
	void CreateStatsWidget();
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** Input callbacks */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	void Spell1(const FInputActionValue& Value);
	void Spell2(const FInputActionValue& Value);
	void Spell3(const FInputActionValue& Value);

	UPROPERTY()
	TArray<AActor*> OverlappingInteractables;

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void AddInteractable(AActor* Interactable);

	// Déclare la fonction RemoveInteractable de la même manière
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RemoveInteractable(AActor* Interactable);
};
