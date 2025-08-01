// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AIController/Default_AIController.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class MMOAT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ASC, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* ASC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI_Attributes")
	UAttributeSet* IA_Attributes;

	UPROPERTY(EditDefaultsOnly, Category = "GA_Attack")
	TSubclassOf<UGameplayAbility> GA_Attack;
	
public:

	/**
	 * Initialize Attribute Set
	 */
	void InitAttributes();

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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Default_Attack")
	bool Default_Attack(AActor* Target);
};
