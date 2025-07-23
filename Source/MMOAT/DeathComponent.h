// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeathComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMOAT_API UDeathComponent : public UActorComponent
{
	GENERATED_BODY()

private:

protected:
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

	
	

public:

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
