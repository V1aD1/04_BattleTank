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

	if (!ensure(ThisTank)) {
		return;
	}

	if (!ensure(PlayerTank)) {
		return;
	}

	//move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //todo check radius is in cm

	//aim at the player
	ThisTank->AimAt(PlayerTank->GetActorLocation());

	//fire at the player
	//ThisTank->Fire();
}

