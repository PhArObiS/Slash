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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed();
	virtual void Attack() override;
	virtual void Jump() override;
	void Dodge();

	/** Combat */
	void EquipWeapon(AWeapon* Weapon);
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	void PlayEquipMontage(const FName& SectionName);
	
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();


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
	 
	 
private:
	/** Character components */
	
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
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
