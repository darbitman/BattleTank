// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  auto TankVelocity = GetComponentVelocity();
  auto TankRightVector = GetRightVector();
  auto SlippageSpeed = FVector::DotProduct(TankVelocity, TankRightVector);

  // Work out the required acceleration this frame to correct
  auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
  
  // Calculate the apply sideways force
  auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
  auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2.0;  // Divide by two since 2 tracks
  //CorrectionForce.Z = 0.0;
  TankRoot->AddForceAtLocation(CorrectionForce, GetComponentLocation());
}

void UTankTrack::SetThrottle(float Throttle)
{
  auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
  auto ForceLocation = GetComponentLocation();
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}