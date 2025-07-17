// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MMOATCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMMOATCharacter : public ACharacter
{
	GENERATED_BODY()

private:

protected:
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ASC, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* ASC;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = GameplayTags, meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer StartingTags;

public:

private:
	

protected:

	// To add mapping context
	virtual void BeginPlay();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SetStats)
	void SetHealth(float MaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SetStats)
	void SetMana(float MaxMana);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SetStats)
	void SetRegens(float HealthRegen, float ManaRegen);

public:
	AMMOATCharacter();

	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

