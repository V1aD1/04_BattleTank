// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/Classes/GameFramework/Controller.h"
#include "BattleTank.h"
#include "Tank.h" //needed to implement OnDeath
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

	//if aim or locked, then fire
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		TankAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank has died"))
}

