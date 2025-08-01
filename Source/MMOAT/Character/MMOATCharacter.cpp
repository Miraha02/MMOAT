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

	DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("DeathComponent"));
	IS_NOT_NULL(DeathComponent, "Death Component Creation Failed");
	DeathComponent->bDestroyOnDeath = false;
	DeathComponent->OnDeath.AddDynamic(this, &AMMOATCharacter::OnDeath);

	
}

void AMMOATCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	IS_NOT_NULL(CharacterData, "Character Data Table Has Not Been Filled in Blueprint !");
	IS_NOT_NULL(GE_HealthRegen, "Health Regen Has Not Been Filled in BP !");
	IS_NOT_NULL(GE_ManaRegen, "Mana Regen Has Not Been Filled in BP !");

	InitAttributes();
	//Add Blueprint choosed Tag to Character's ASC 
	ASC->AddLooseGameplayTags(StartingTags);

	//Set Character Stats From Character Data Asset
	SetHealth(CharacterData->GetMaxHealth());
	SetMana(CharacterData->GetMaxMana());
	SetRegens(CharacterData->GetHealthRegen(), CharacterData->GetManaRegen());

	OnHealthUpdateEvent();
	OnManaUpdateEvent();

	// Apply Gameplay Effect Regens to Character
	FGameplayEffectContextHandle HealthSpecHandle = ASC->MakeEffectContext();
	FGameplayEffectContextHandle ManaSpecHandle = ASC->MakeEffectContext();
	HealthSpecHandle.AddSourceObject(this);
	ManaSpecHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GE_HealthRegen, 0, HealthSpecHandle);
	if (SpecHandle.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	SpecHandle = ASC->MakeOutgoingSpec(GE_ManaRegen, 0, ManaSpecHandle);
	if (SpecHandle.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}

	
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

void AMMOATCharacter::OnDeath_Implementation()
{
	FGameplayTag AliveTag = FGameplayTag::RequestGameplayTag(FName("Character.IsAlive"));
	FGameplayTag DeadTag = FGameplayTag::RequestGameplayTag(FName("Character.IsDead"));

	UE_LOG(LogTemp, Display, TEXT("%s is Dead"),*GetName());

	// Le player est Déjà mort
	if (ASC->HasMatchingGameplayTag(DeadTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is already Dead, OnDeath Function Should not be call twice or more"));
		return;
	}

	// Add and remove Alive and Dead Tags
	ASC->AddLooseGameplayTag(DeadTag);
	ASC->AddReplicatedLooseGameplayTag(DeadTag);
	if (ASC->HasMatchingGameplayTag(AliveTag))
	{
		ASC->RemoveLooseGameplayTag(AliveTag);
		ASC->RemoveReplicatedLooseGameplayTag(AliveTag);
	}
	
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
		if (!ASC->HasMatchingGameplayTag(HealthTag))
		{
			UE_LOG(LogTemp, Display, TEXT("Activating Health Regen"));
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
		if (!ASC->HasMatchingGameplayTag(FullHealthTag))
		{
			UE_LOG(LogTemp, Display, TEXT("Deactivating Health Regen"));
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

void AMMOATCharacter::ActivateManaRegen(bool Activate)
{
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Error, ASC is Null !!!"))
		return;
	}
		
	FGameplayTag ManaTag = FGameplayTag::RequestGameplayTag(FName("Character.Mana.MissMana"));
	FGameplayTag FullManaTag = FGameplayTag::RequestGameplayTag(FName("Character.Mana.IsFullMana"));

	// Activate Mana Regen
	if (Activate)
	{
		if (!ASC->HasMatchingGameplayTag(ManaTag))
		{
			UE_LOG(LogTemp, Display, TEXT("Activating Mana Regen"));
			ASC->AddLooseGameplayTag(ManaTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Mana.MissMana' Has been Added to %s"), *GetName());
		}
		if (ASC->HasMatchingGameplayTag(FullManaTag))
		{
			ASC->RemoveLooseGameplayTag(FullManaTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Mana.IsFullMana' Has Been removed From %s"), *GetName());
		}
	}
	// Deactivate Mana Regen
	else
	{
		if (!ASC->HasMatchingGameplayTag(FullManaTag))
		{
			UE_LOG(LogTemp, Display, TEXT("Deactivating Mana Regen"));
			ASC->AddLooseGameplayTag(FullManaTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Mana.IsFullMana' Has been Added to %s"), *GetName());
		}
		if (ASC->HasMatchingGameplayTag(ManaTag))
		{
			ASC->RemoveLooseGameplayTag(ManaTag);
			UE_LOG(LogTemp, Display, TEXT("Tag 'Character.Mana.MissMana' Has Been removed From %s"), *GetName());
		}
	}
}

#define LAUNCH_SPELLS(SpellClass, SpellName)\
UE_LOG(LogTemp, Display, TEXT("Launching %hs ..."), SpellName);\
if (!SpellClass)\
{\
	UE_LOG(LogTemp, Warning, TEXT("No %s Defined !"), TEXT(SpellName));\
}\
ASC->TryActivateAbilityByClass(SpellClass);

void AMMOATCharacter::LaunchSpell1()
{
	LAUNCH_SPELLS(Spells.Spell1, "Spell 1");
}

void AMMOATCharacter::LaunchSpell2()
{
	LAUNCH_SPELLS(Spells.Spell2, "Spell 2");
}

void AMMOATCharacter::LaunchSpell3()
{
	LAUNCH_SPELLS(Spells.Spell3, "Spell 3");
}
