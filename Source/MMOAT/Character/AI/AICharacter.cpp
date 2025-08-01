// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MMOAT/Err.h"
#include "MMOAT/GAS/AttributeSets/EnnemyAttributeSet.h"


// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	IS_NOT_NULL(ASC, "Ability System Component Creation Failed");
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);

	InitAttributes();

	IS_NOT_NULL(GA_Attack, "GA_Attack class has not been filled in AICharacter Blueprint SubClass")
	IS_NOT_NULL(DataAsset, "DataAsset class has not been filled in Blueprint")
	IS_NOT_NULL(GE_SetStats, "GE_SetStats class has not been filled in Blueprint");

	SetStats(DataAsset->GetMaxHealth(), DataAsset->GetDamage());
	
	if (HasAuthority())
	{
		ASC->GiveAbility(GA_Attack);
		ASC->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AAICharacter::Default_Attack_Implementation(AActor* Target)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Target Found"));
		return false;
	}

	
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.AI.Attack"));
	EventData.Instigator = this;
	EventData.Target = Target;
	EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Target);

	UE_LOG(LogTemp, Display, TEXT("Launching IA's ATTACK"));
	ASC->HandleGameplayEvent(EventData.EventTag, &EventData);

	return true;
}

void AAICharacter::InitAttributes()
{
	IA_Attributes = NewObject<UEnnemyAttributeSet>(this, UEnnemyAttributeSet::StaticClass());
	ASC->AddAttributeSetSubobject(IA_Attributes);
}

void AAICharacter::SetStats_Implementation(float Maxhealth, float Damage)
{
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GE_SetStats, 1.f, EffectContext);

	if (SpecHandle.IsValid() && DataAsset)
	{

		UE_LOG(LogTemp, Display, TEXT("Set %s Stats"), *GetName());
		
		SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Stats.HealthMax")), Maxhealth);
		SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Stats.Damage")), Damage);

		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
