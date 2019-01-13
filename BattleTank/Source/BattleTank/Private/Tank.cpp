// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
  // Initialize LastFireTime to the moment the tank is created
  LastFireTime = FPlatformTime::Seconds();

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
  TankAimingComponent->AimAt(HitLocation, ProjectileLaunchSpeed);
}

void ATank::Fire()
{
  bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
  if (Barrel && bIsReloaded)
  {
    // Spawn a projectile at the socket location on the barrel
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
      ProjectileBlueprint,
      Barrel->GetSocketLocation(FName("Projectile")),
      Barrel->GetSocketRotation(FName("Projectile"))
      );

    Projectile->LaunchProjectile(ProjectileLaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}
