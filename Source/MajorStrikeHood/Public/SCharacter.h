// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;

UCLASS()
class MAJORSTRIKEHOOD_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void PrimaryAttack();
	void PrimaryInteract();

	UPROPERTY(EditAnywhere)
	TSubclassOf <AActor> ProjectileClass;

private:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <USInteractionComponent> InteractionComp;

};
