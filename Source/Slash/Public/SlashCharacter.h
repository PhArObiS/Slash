// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class UInputMappingContext;
class UInputAction; 


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

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* SlashMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpingAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EKeyAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* DodgeAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	/** Callbacks for input */
	// void MoveForward(float Value);
	// void MoveRight(float Value);
	void EKeyPressed();
	virtual void Attack();
	void Dodge();
	
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent *CameraBoom;
   
	UPROPERTY(VisibleAnywhere)
	UCameraComponent *ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;
	
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;
};
