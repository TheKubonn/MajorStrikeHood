// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class MAJORSTRIKEHOOD_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASItemChest();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr <UStaticMeshComponent> ChestMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr <UStaticMeshComponent> LidMesh;

private:

	UPROPERTY(EditAnywhere, Category = "Mesh Properties", meta = (AllowPrivateAccess = "true"))
	float TargetPitch;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
