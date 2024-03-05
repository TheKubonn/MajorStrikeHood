// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"

ASItemChest::ASItemChest() :
	TargetPitch(110.f)
{
	PrimaryActorTick.bCanEverTick = true;

	ChestMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("ChestMesh"));
	SetRootComponent(ChestMesh);

	LidMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(ChestMesh);

}

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}

