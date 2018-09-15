// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "BattleTank.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto NewRotation = RelativeRotation.Yaw + RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0, NewRotation, 0));

	UE_LOG(LogTemp, Warning, TEXT("turret rotation: %f"), NewRotation)
}

