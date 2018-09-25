// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto ThisTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ThisTank) {
		return;
	}

	if (!PlayerTank) {
		return;
	}

	//move towards the player

	//aim at the player
	ThisTank->AimAt(PlayerTank->GetActorLocation());

	//fire at the player
	ThisTank->Fire();
}

