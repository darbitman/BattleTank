// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  auto ControlledTank = GetControlledTank();
  if (!ControlledTank)
  {
    UE_LOG(LogTemp, Error, TEXT("PlayerController not possesing a tank"));
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *(ControlledTank->GetName()));
  }
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
  if (!GetControlledTank()) { return; }
  
  FVector HitLocation;  // Out parameter
  if (GetSightRayHitLocation(HitLocation))  // Has "side-effect", is going to line trace
  {
    UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
    // TODO Tell controlled tank to aim at this point
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Did not hit anything in world"));
  }

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
  return false;
}
