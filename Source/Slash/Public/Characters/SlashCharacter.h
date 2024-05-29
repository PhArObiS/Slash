// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Characters/CharacterTypes.h"
#include "InputMappingContext.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class UInputMappingContext;
class UInputAction;
class AItem;
class UAnimMontage;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;  
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	
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
	virtual void Attack() override;
	virtual void Jump() override;
	void Dodge();

	/**
	 * Play montage functions
	 */
	
	virtual void PlayAttackMontage() override;
	virtual bool CanAttack() override;
	
	virtual void AttackEnd() override;

	void PlayEquipMontage(const FName& SectionName);
	bool CanDisarm();
	bool CanArm();

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	 
	 
private:
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
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
	UAnimMontage* EquipMontage;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
