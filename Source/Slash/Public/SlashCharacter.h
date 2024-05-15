// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Characters/CharacterTypes.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class UInputMappingContext;
class UInputAction;
class AItem;
class UAnimMontage;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;  
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputMappingContext* SlashMappingContext;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* JumpingAction;
	
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* EKeyAction;
	
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* DodgeAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void EKeyPressed();
	virtual void Attack();
	void Dodge();
	
private:
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent *CameraBoom;
   
	UPROPERTY(VisibleAnywhere)
	UCameraComponent *ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;
	
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	/**
	 * Animation montages
	 */

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
