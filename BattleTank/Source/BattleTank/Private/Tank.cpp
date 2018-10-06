// Copyright Vlad Baderca
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Engine/Classes/Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) const {
	if (!TankAimingComponent){return;}

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {

	if (!TankAimingComponent) { return; }

	UTankBarrel* Barrel = TankAimingComponent->GetBarrel();
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!Barrel || !IsReloaded)
	{
		return;
	}


	if (Barrel->DoesSocketExist("Projectile")) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}