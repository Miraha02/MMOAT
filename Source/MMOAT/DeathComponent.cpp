// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathComponent.h"

// Sets default values for this component's properties
UDeathComponent::UDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UDeathComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UDeathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

