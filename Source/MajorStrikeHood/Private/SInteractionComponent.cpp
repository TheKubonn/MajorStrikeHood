// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotation;
	AActor* MyOwner = GetOwner();
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 200.f);

	// One way to do line trace, however it's small so people playing on game pad might have problem to hit the objects
	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	// Second way to do the line trace which is multi not single
	TArray <FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(30.f);

	// FQuat::Identity means no rotation applied
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.f, 32, LineColor, false, 3.f);
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 3.f);

}

