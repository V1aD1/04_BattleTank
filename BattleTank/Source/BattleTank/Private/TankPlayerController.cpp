// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("in playerController"))
}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* ControlledTank =  Cast<ATank>(GetPawn());
	
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Controller tank name: %s"), *ControlledTank->GetName())
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("No player controller tank found!!"))
	}

	return ControlledTank;
}


