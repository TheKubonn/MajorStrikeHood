// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject <USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	//SpringArmComp->TargetArmLength = 600.f;

	CameraComp = CreateDefaultSubobject <UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));
	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("PrimaryInteract"), IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.f;
		ControlRot.Roll = 0.f;

		AddMovementInput(ControlRot.Vector(), Value);
	}
}

void ASCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.f;
		ControlRot.Roll = 0.f;

		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);
	}
}

void ASCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	GetWorld()->SpawnActor <AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

