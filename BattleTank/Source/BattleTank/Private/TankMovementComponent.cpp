// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
  // TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
  // TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  LeftTrack->SetThrottle(-Throw);
  RightTrack->SetThrottle(Throw);
  // TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  // No need to call Super as we're replacing the functionality
  auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();
  auto ForwardThrow = FVector::DotProduct(TankForwardVector, AIForwardIntention);

  IntendMoveForward(ForwardThrow);
  //UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *AIForwardIntention);
}
