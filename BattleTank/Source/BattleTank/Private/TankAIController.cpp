// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank)) { return; }
	if (!ensure(TankAimingComponent)) { return; }

	//move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //todo check radius is in cm

	//aim at the player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	//fire at the player
	TankAimingComponent->Fire();
}

