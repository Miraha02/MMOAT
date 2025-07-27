// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeathComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

/**
 * UDeathComponent is used to define all logics around actor's Death
 *
 * You can add this Component to Any Actor that should die and/or be destroyed
 *
 * To implement function you can either :
 *	- create a SubClass of UDeathComponent And implement the HandleDeath
 * Function
 *	- Bind Every logics you need on Actor Death to the OnDeath Property
 *
 *	The Implemented Logics will be Executed after calling the Die Function weither it has
 *	been implemented via a SubClass of UDeathComponent or via Binding events to OnDeath Property
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMOAT_API UDeathComponent : public UActorComponent
{
	GENERATED_BODY()

private:

protected:

public:
	
	/**
	 * Indicate if the component Should Destroy The Actor On Death
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destroy", meta = (AllowPrivateAccess = "true"))
	bool bDestroyOnDeath = true;

	/**
	 * Delay Before Actor Destruction if bDestroyOnDeath = true
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destroy", meta = (AllowPrivateAccess = "true"))
	float DelayBeforeDestroy = 3.0f;

private:
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UDeathComponent();

	/** Call Character's death */
	UFUNCTION(BlueprintCallable, Category = "Death")
	void Die();
	
	/** Used to specify actor's death */
	UFUNCTION(BlueprintNativeEvent, Category = "Death")
	void HandleDeath();
	
	virtual void HandleDeath_Implementation();
	
	/** Used to trigger all bound functions */
	UPROPERTY(BlueprintAssignable, Category = "Death")
	FOnDeathSignature OnDeath;
		
};
