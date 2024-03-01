// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SCharacter.h"

ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BarrelMesh"));
	SetRootComponent(BarrelMesh);
	BarrelMesh->SetSimulatePhysics(true);
	// When we are enabling "Simulate Physics" in blueprints, it automatically change our collision profile to PhysicsActor, in C++ you have to do this manually
	BarrelMesh->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	RadialForce = CreateDefaultSubobject <URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->Radius = 500.f;
	// Ignores mass of other objects, if false impulse strength will be much higher to push most objects depending of their mass
	RadialForce->bImpulseVelChange = true;
	RadialForce->ImpulseStrength = 2500.f; // if bImpulseVelChange would be false, good value for the strength would be 200000.f
	// Default constructor does not contain WorldDynamic to affect
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	

}


void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BarrelMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

