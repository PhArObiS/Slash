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
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"


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
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->AddRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
	ViewCamera->bUsePawnControlRotation = false;
	

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

void ASlashCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}

void ASlashCharacter::Move(const FInputActionValue &Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.Y > 0.05f || MovementVector.Y < -0.05f)
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementVector.Y);	
	}

	if (MovementVector.X > 0.05f || MovementVector.X < -0.05f)
	{
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementVector.X);
	}

}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
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
}

void ASlashCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
	else
	{
		if (CanDisarm())
		{
			PlayEquipMontage(FName("Unequip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
		else if (CanArm())
		{
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
	}
}

void ASlashCharacter::Attack() 
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

bool ASlashCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanDisarm() 
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter:: CanArm() 
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
			EquippedWeapon;
}

void ASlashCharacter::Disarm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void ASlashCharacter::Arm()
{
	EquippedWeapon->AttachToSocket(GetMesh(), FName("RightHandSocket"));
}

void ASlashCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		const int32 Selection = FMath::RandRange(0,2);
		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		case 2:
			SectionName = FName("Attack3");
			break;
		case 3:
			SectionName = FName("Attack4");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void ASlashCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayEquipMontage called. SectionName: %s"), *SectionName.ToString());
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayEquipMontage failed. AnimInstance or EquipMontage is nullptr."));
	}
}

void ASlashCharacter::Dodge()
{
	return;
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
// }


