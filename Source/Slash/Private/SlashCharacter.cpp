// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GroomComponent.h"
#include "Slash/Item.h"
#include "Slash/Weapons/Weapon.h"


ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.F;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");
	
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
}

void ASlashCharacter::BeginPlay() 
{
	Super::BeginPlay();

	if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SlashMappingContext, 0);
		}
	}
}

void ASlashCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementVector.Y);
	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MovementVector.X);

}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Debug message to check if the Look function is being called
	UE_LOG(LogTemp, Warning, TEXT("Look function called."));

	if (Controller)
	{
		// Debug message to print out the input values
		UE_LOG(LogTemp, Warning, TEXT("Look Axis Vector X: %f, Y: %f"), LookAxisVector.X, LookAxisVector.Y);

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashCharacter::Jump()
{
	Super::Jump();
	// if (IsUnoccupied())
	// {
	// 	Super::Jump();
	// }
}

void ASlashCharacter::Attack() 
{
	return;
}

void ASlashCharacter::Dodge()
{
	return;
}

void ASlashCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
	}
}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpingAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Jump);
		
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
	}
}

// void ASlashCharacter::Move(const FInputActionValue &Value)
// {
// 	
// 	if (!Controller)
// 	{
// 		return;
// 	}
// 	
// 	// if (ActionState != EActionState::EAS_Unoccupied) return;
// 	const FVector2D MovementVector = Value.Get<FVector2D>();
// 	const FRotator Rotation = Controller->GetControlRotation();
// 	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
// 	
// 	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 	AddMovementInput(ForwardDirection, MovementVector.Y);
// 	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 	AddMovementInput(RightDirection, MovementVector.X);
//
//
// }

// void ASlashCharacter::Move(const FInputActionValue &Value)
// {
// 	const FVector2D MovementVector = Value.Get<FVector2D>();
// 	const FRotator MoveRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
// 	
//
// 	if (MovementVector.X > 0.05f || MovementVector.X < -0.05f)
// 	{
// 		const FVector Right = MoveRotation.RotateVector(FVector::RightVector);
// 		AddMovementInput(Right, MovementVector.X);
// 	}
//
// 	if (MovementVector.Y > 0.05f || MovementVector.Y < -0.05f)
// 	{
// 		const FVector Forward = MoveRotation.RotateVector(FVector::ForwardVector);
// 		AddMovementInput(Forward, MovementVector.Y);
// 	}
//
// }


// void ASlashCharacter::MoveForward(float Value)
// {
// 	if (!Controller)
// 	{
// 		return;
// 	}
//
// 	// if (ActionState != EActionState::EAS_Unoccupied) return;
// 	if (Controller && (Value != 0.f))
// 	{
// 		// find out which way is forward
// 		const FRotator ControlRotation = Controller->GetControlRotation();
// 		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
//
// 		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 		AddMovementInput(Direction, Value);
// 	}
// }

// void ASlashCharacter::MoveRight(float Value)
// {
// 	
// 	// if (ActionState != EActionState::EAS_Unoccupied) return;
// 	if (Controller && (Value != 0.f))
// 	{
// 		// find out which way is right
// 		const FRotator ControlRotation = GetControlRotation();
// 		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
//
// 		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 		AddMovementInput(Direction, Value);
// 	}
// }




