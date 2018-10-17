// Copyright Vlad Baderca
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"
#include "Projectile.h"


void  UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

UTankAimingComponent::UTankAimingComponent() {
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();

	//so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo <= 0) { FiringState = EFiringState::OutOfAmmo; }
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) { FiringState = EFiringState::Reloading; }
	else if (IsBarrelMoving()) { FiringState = EFiringState::Aiming; }
	else { FiringState = EFiringState::Locked; }
	
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}

bool UTankAimingComponent::IsBarrelMoving() const {
	if (!ensure(Barrel)) { return false; }

	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


	if (UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //param necessary for funtion to succeed every frame
	))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}

	else {
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time)
	}
}

UTankBarrel* UTankAimingComponent::GetBarrel()
{
	return Barrel;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel)) {
		return;
	}

	//work out difference between current barrel rotation and aimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); //todo remove magic number
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	if (!ensure(Turret)) {
		return;
	}

	auto CurrentTurretRot = Turret->GetForwardVector().Rotation();
	auto AimRot = AimDirection.Rotation();
	auto DeltaRotation = AimRot - CurrentTurretRot;

	if (FMath::Abs(DeltaRotation.Yaw) > 180) {
		Turret->Rotate(-DeltaRotation.Yaw);
	}
	else {
		Turret->Rotate(DeltaRotation.Yaw);
	}
}

void UTankAimingComponent::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("firing"))
	
	if (FiringState == EFiringState::Reloading) { return; }

	if (FiringState == EFiringState::OutOfAmmo) { return; }

	if (Barrel->DoesSocketExist("Projectile")) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		Ammo--;
	}
}


