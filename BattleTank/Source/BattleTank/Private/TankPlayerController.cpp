// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto tank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	ATank* ControlledTank = Cast<ATank>(GetPawn());

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


	FVector OutHitLocation; // out param

	//get world location thorugh crosshair
	if (GetSightRayHitLocation(OutHitLocation)) {
		//aim barrell at this point
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


		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString())


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

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + LookDirection*LineTraceRange, ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);

	return false;
}
