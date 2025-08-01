// Fill out your copyright notice in the Description page of Project Settings.


#include "Default_AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MMOAT/Character/MMOATCharacter.h"
#include "MMOAT/Character/AI/AICharacter.h"


// Sets default values
ADefault_AIController::ADefault_AIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADefault_AIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefault_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetNearestPlayerInBlackboard();
	
}

bool ADefault_AIController::Default_Attack()
{
	AAICharacter* AIChar = Cast<AAICharacter>(GetPawn());
	if (AIChar)
	{
		return AIChar->Default_Attack(NearestPlayer);
	}
	return false;
}


void ADefault_AIController::SetNearestPlayerInBlackboard()
{
	if (!BlackboardComp)
	{
		BlackboardComp = GetBlackboardComponent();
	}

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return ;

	FVector MyLocation = ControlledPawn->GetActorLocation();
	UWorld* World = GetWorld();
	if (!World) return ;

	AMMOATCharacter* ClosestCharacter = nullptr;
	float ClosestSqrDistance = MAX_flt;

	for (TObjectIterator<AMMOATCharacter> It; It; ++It)
	{
		AMMOATCharacter* TestChar = *It;

		if (!IsValid(TestChar) || TestChar == ControlledPawn || TestChar->GetWorld() != World)
			continue;

		// Check That Char is Alive
		if (!TestChar->ActorHasTag("Character.IsAlive") || TestChar->ActorHasTag("Character.IsDead"))
			continue;
		
		float SqrDist = FVector::DistSquared(MyLocation, TestChar->GetActorLocation());
		if (SqrDist < ClosestSqrDistance)
		{
			ClosestSqrDistance = SqrDist;
			ClosestCharacter = TestChar;
		}
	}
	if (ClosestCharacter)
	{
		NearestPlayer = ClosestCharacter;
		BlackboardComp->SetValueAsVector("PlayerLocation",ClosestCharacter->GetActorLocation());
	} else
	{
		BlackboardComp->ClearValue("PlayerLocation");
		NearestPlayer = nullptr;
	}
}
