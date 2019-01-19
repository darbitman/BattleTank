#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if (!ensure(LeftTrack && RightTrack)) { return; }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
  if (!ensure(LeftTrack && RightTrack)) { return; }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  // No need to call Super as we're replacing the functionality
  auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();

  auto ForwardThrow = FVector::DotProduct(TankForwardVector, AIForwardIntention);
  IntendMoveForward(ForwardThrow);

  auto RightTurnThrow = FVector::CrossProduct(TankForwardVector, AIForwardIntention).Z;
  IntendTurnRight(RightTurnThrow);
}
