// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ThisTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (ThisTank)
		UE_LOG(LogTemp, Warning, TEXT("Player tank is: %s"), *ThisTank->GetName());

	if (PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("Player tank is: %s"), *PlayerTank->GetName());
}

ATank* ATankAIController::GetControlledTank() const {
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if(!ControlledTank){
		UE_LOG(LogTemp, Warning, TEXT("No AI controller tank found!!"));
	}

	return ControlledTank;
}

ATank* ATankAIController::GetPlayerTank() const {
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("No player tank found!"));
	}

	return PlayerTank;
}
