// Fill out your copyright notice in the Description page of Project Settings.

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


	FVector OutHitLocation; // out param

	//get world location thorugh crosshair
	if (GetSightRayHitLocation(OutHitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *OutHitLocation.ToString());
		//aim barrell at this point
	}
		

}

// Returns true and populates OutHitLocation if crosshair is hitting something
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find crosshair position on screen
	int32 ViewPortSizeX, ViewPortSizeY;	
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);

	//de-project screen position to world direction

	//line trace along look direction

	//see what we hit

	return true;
}

