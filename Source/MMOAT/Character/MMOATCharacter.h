// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MMOATCharacterData.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MMOAT/DeathComponent.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	UMMOATCharacterData* CharacterData;

	UPROPERTY(EditDefaultsOnly, Category = GameplayEffect)
	TSubclassOf<UGameplayEffect> GE_HealthRegen;

	UPROPERTY(EditDefaultsOnly, Category = GameplayEffect)
	TSubclassOf<UGameplayEffect> GE_ManaRegen;

	UPROPERTY(EditDefaultsOnly, Category = DeathComponent)
	UDeathComponent* DeathComponent;
	

public:

private:
	/**
	 * Initialize Character Attribute Set
	 */
	void InitAttributes();
	

protected:

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SetStats)
	void SetHealth(float MaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SetStats)
	void SetMana(float MaxMana);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SetStats)
	void SetRegens(float HealthRegen, float ManaRegen);

	UFUNCTION(BlueprintNativeEvent, Category = "Event/Death")
	void OnDeath();

public:
	AMMOATCharacter();

	/**
	* Activate or Deactivate Health Regen on the Character By granting and removing concerned Tags
	* @param Activate true : Activate HealthRegen \n false : Deactivate HealthRegen
	*/
	UFUNCTION(BlueprintCallable, Category = SetStats)
	void ActivateHealthRegen(bool Activate = true);

	/**
	* Activate or Deactivate Mana Regen on the Character by granting and removing concerned Tags
	* @param Activate true : Activate ManaRegen \n false : Deactivate ManaRegen
	*/
	UFUNCTION(BlueprintCallable, Category = SetStats)
	void ActivateManaRegen(bool Activate = true);

	UFUNCTION(BlueprintNativeEvent, Category = "Event/UI_Function")
	void OnHealthUpdateEvent();

	UFUNCTION(BlueprintNativeEvent, Category = "Event/UI_Function")
	void OnManaUpdateEvent();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

