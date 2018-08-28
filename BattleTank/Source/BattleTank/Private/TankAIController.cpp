// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto tank = GetControlledTank();
}

ATank* ATankAIController::GetControlledTank() const {
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller tank name: %s"), *ControlledTank->GetName())
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("No player controller tank found!!"))
	}

	return ControlledTank;
}


