// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

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
     UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
    // TODO Tell controlled tank to aim at this point
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Did not hit anything in world"));
  }

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
  // Find the crosshair position in pixel coordinates
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  FVector2D ScreenLocation(
    (float)ViewportSizeX * CrosshairXLocation,
    (float)ViewportSizeY * CrosshairYLocation
  );

  // "Deproject" screen position of the crosshair to a world direction
  FVector LookDirection;
  if (GetLookDirection(ScreenLocation, LookDirection))
  {
    // Line-trace along that direction, and see what we hit (up to max range)
    return GetLookVectorHitLocation(LookDirection, OutHitLocation);
  }
  return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& OutLookDirection) const
{
  FVector CameraWorldLocation;  // unused, but must be passed in
  return DeprojectScreenPositionToWorld(
    ScreenLocation.X,
    ScreenLocation.Y,
    CameraWorldLocation,
    OutLookDirection
  );
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
  FHitResult HitResult;
  auto StartLocation = PlayerCameraManager->GetCameraLocation();
  auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
  if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility))
  {
    HitLocation = HitResult.Location;
    return true;
  }
  HitLocation = FVector(0);
  return false;
}
