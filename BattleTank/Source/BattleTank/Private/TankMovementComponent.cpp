// Copyright Vlad Baderca

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"

void UTankMovementComponent::InitialiseProperties(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

//won't be calling super since we're completely overriding the method
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {

	auto AiForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct(AiForwardIntention, TankForward);
	auto RightThrow = FVector::CrossProduct(AiForwardIntention, TankForward);


	UE_LOG(LogTemp, Warning, TEXT("%s dot product: %f"), *GetOwner()->GetName(), -RightThrow.Z)

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow.Z);
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//todo prevent double speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//todo prevent double speed due to dual control use
}