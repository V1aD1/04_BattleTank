// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ThisTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (ThisTank)
		UE_LOG(LogTemp, Warning, TEXT("This tank is: %s"), *ThisTank->GetName());

	if (PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("Player tank is: %s"), *PlayerTank->GetName());
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* ThisTank = GetControlledTank();

	if (!ThisTank) {
		return;
	}

	if (!GetPlayerTank()) {
		return;
	}

	//move towards the player


	//aim at the player
	ThisTank->AimAt(GetPlayerTank()->GetActorLocation());

	//fire at the player
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

