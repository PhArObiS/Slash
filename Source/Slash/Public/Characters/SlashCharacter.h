// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Characters/CharacterTypes.h"
#include "InputMappingContext.h"
#include "Interfaces/PickupInterface.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class UInputMappingContext;
class UInputAction;
class ASoul;
class ATreasure;
class AItem;
class UAnimMontage;
class USlashOverlay;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;
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
	virtual void DodgeEnd() override;
	virtual bool CanAttack() override;
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	void PlayEquipMontage(const FName& SectionName);
	virtual void Die() override;
	bool IsOccupied();
	bool HasEnoughStamina();
	
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

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
	bool IsUnoccupied();
	void InitializeInputSubsystem();
	void InitializeSlashOverlay();
	void SetHUDHealth();
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

	UPROPERTY()
	USlashOverlay* SlashOverlay;
public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
