// Copyright Epic Games, Inc. All Rights Reserved.

#include "MMOATCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MMOAT/Err.h"
#include "MMOAT/GAS/AttributeSets/CharacterAttributeSet.h"
#include "MMOAT/GAS/GE/GE_Test_TakeDamage.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMMOATCharacter
AMMOATCharacter::AMMOATCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	IS_NOT_NULL(CameraBoom, "Spring Arm creation Failed");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	IS_NOT_NULL(FollowCamera, "Camera Creation Failed");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	IS_NOT_NULL(ASC, "Ability System Component Creation Failed");

	

	
}

void AMMOATCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	IS_NOT_NULL(CharacterData, "Character Data Table Has Not Been Filled in Blueprint !");

	InitAttributes();
	//Add Blueprint choosed Tag to Character's ASC 
	ASC->AddLooseGameplayTags(StartingTags);

	//Set Character Stats From Character Data Asset
	SetHealth(CharacterData->GetMaxHealth());
	SetMana(CharacterData->GetMaxMana());

	OnHealthUpdateEvent();
	OnManaUpdateEvent();
}

void AMMOATCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(UGE_Test_TakeDamage::StaticClass(), 1.0f, Context);

	if (false && SpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("%f"),ASC->GetSet<UCharacterAttributeSet>()->GetHealth());
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void AMMOATCharacter::InitAttributes()
{
	UCharacterAttributeSet* MyAttributeSet = NewObject<UCharacterAttributeSet>(this, UCharacterAttributeSet::StaticClass());
	ASC->AddAttributeSetSubobject(MyAttributeSet);
}

void AMMOATCharacter::OnDeathEvent_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("AAMMOATCharacter is Dead"));
}

void AMMOATCharacter::SetHealth_Implementation(float MaxHealth)
{
	UE_LOG(LogTemp, Error, TEXT("Set Health function Is Not Implemented in Blueprint !"));
}

void AMMOATCharacter::SetMana_Implementation(float MaxMana)
{
	UE_LOG(LogTemp, Error, TEXT("Set Mana function Is Not Implemented in Blueprint !"));
}

void AMMOATCharacter::SetRegens_Implementation(float HealthRegen, float ManaRegen)
{
	UE_LOG(LogTemp, Error, TEXT("Set Regens function Is Not Implemented !"));
}

void AMMOATCharacter::OnHealthUpdateEvent_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("OnHealthUpdateEvent Is Not Implemented !"));
}

void AMMOATCharacter::OnManaUpdateEvent_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("OnManaUpdateEvent Is Not Implemented !"));
}

void AMMOATCharacter::ActivateHealthRegen(bool Activate)
{
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Error, ASC is Null !!!"))
		return;
	}
		
		FGameplayTag HealthTag = FGameplayTag::RequestGameplayTag(FName("Character.Health.MissHealth"));
		FGameplayTag FullHealthTag = FGameplayTag::RequestGameplayTag(FName("Character.Health.IsFullHealth"));

	// Activate Health Regen
	if (Activate)
	{
		UE_LOG(LogTemp, Display, TEXT("Activating Health Regen"));
		if (!ASC->HasMatchingGameplayTag(HealthTag))
		{
			ASC->AddLooseGameplayTag(HealthTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Health.MissHealth' Has been Added to %s"), *GetName());
		}
		if (ASC->HasMatchingGameplayTag(FullHealthTag))
		{
			ASC->RemoveLooseGameplayTag(FullHealthTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Health.IsFullHealth' Has Been removed From %s"), *GetName());
		}
	}
	// Deactivate Health Regen
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Activating Health Regen"));
		if (!ASC->HasMatchingGameplayTag(FullHealthTag))
		{
			ASC->AddLooseGameplayTag(FullHealthTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Health.IsFullHealth' Has been Added to %s"), *GetName());
		}
		if (ASC->HasMatchingGameplayTag(HealthTag))
		{
			ASC->RemoveLooseGameplayTag(HealthTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Health.MissHealth' Has Been removed From %s"), *GetName());
		}
	}
}