// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class MAJORSTRIKEHOOD_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr <USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr <UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr <UParticleSystemComponent> EffectComp;

private:	
	

};
