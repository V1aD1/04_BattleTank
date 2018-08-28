// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto tank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* ControlledTank =  Cast<ATank>(GetPawn());
	
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller tank name: %s"), *ControlledTank->GetName());
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("No player controller tank found!!"));
	}

	return ControlledTank;
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	//get world location thorugh crosshair
	//if it  hits landscape
		//aim barrell at this point

}

