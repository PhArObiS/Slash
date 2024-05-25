// Fill out your copyright notice in the Description page of Project Settings.

#include "Breakable/BreakableActor.h"

ABreakableActor::ABreakableActor()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

