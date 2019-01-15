// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  // TODO remove once Fire() is moved to AimingComponent
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ProjectileLaunchSpeed = 4000.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0f;

  // Local barrel reference to be used for spawning projectile
  UTankBarrel* Barrel = nullptr;  // TODO remove from Tank

  double LastFireTime = 0.0;
};
