// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slash/Item.h"
#include "Weapon.generated.h"

class USoundBase;

/**
 * 
 */
UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	void Equip(USceneComponent* InParent, FName InSocketName);
	void AttachToSocket(USceneComponent* InParent, FName InSocketName);
	
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex) override;

private:

	UPROPERTY(EditAnywhere, Category = " Weapon Properties")
	USoundBase* EquipSound;
	
};
