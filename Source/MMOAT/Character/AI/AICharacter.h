// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AIController/Default_AIController.h"
#include "GameFramework/Character.h"
#include "MMOAT/ActorComponent/EnnemyDeathComponent.h"
#include "MMOAT/Character/Data/EnnemyDataAsset.h"
#include "AICharacter.generated.h"

UCLASS()
class MMOAT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ASC, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* ASC;
	
	UPROPERTY(BlueprintReadWrite, Category = "AI_Attributes")
	UAttributeSet* IA_Attributes;

	UPROPERTY(EditDefaultsOnly, Category = "GA_Attack")
	TSubclassOf<UGameplayAbility> GA_Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	UEnnemyDataAsset* DataAsset;

	UPROPERTY(EditDefaultsOnly, Category = GE_SetStats)
	TSubclassOf<UGameplayEffect> GE_SetStats;

	UPROPERTY(EditDefaultsOnly, Category = DeathComponent)
	UEnnemyDeathComponent* DeathComponent;
	
public:

	/**
	 * Initialize Attribute Set
	 */
	void InitAttributes();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Stats")
	void SetStats(float Maxhealth, float Damage);

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
