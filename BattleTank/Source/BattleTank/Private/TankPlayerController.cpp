// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No player controller tank found!!"));
	}

	return ControlledTank;
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(GetControlledTank())) {
		return;
	}


	FVector HitLocation; // out param

	//get world location thorugh crosshair
	if (GetSightRayHitLocation(HitLocation)) {
		//aim barrel at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Returns true and populates OutHitLocation if crosshair is hitting something
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find crosshair position on screen
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);

	//de-project screen position to world direction
	FVector ScreenDirection;
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {

		//line trace along look direction
		GetLookVectorHitLocation(LookDirection, HitLocation);


		//see what we hit
	}



	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector WorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + LookDirection * LineTraceRange, ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);

	return false;
}
