// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	//How close will the AI Tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 10000;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();
};
