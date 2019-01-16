// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
  Reloading,
  Aiming,
  Locked
};

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "Setup")
  void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

  void AimAt(FVector HitLocation);

  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();

protected:
  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringState FiringState = EFiringState::Reloading;

private:
  // Sets default values for this component's properties
  UTankAimingComponent();

  // Called when the game starts
  virtual void BeginPlay() override;

  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

  void MoveBarrelTowards(FVector AimDirection);

  UTankBarrel* Barrel = nullptr;

  UTankTurret* Turret = nullptr;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ProjectileLaunchSpeed = 4000.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0f;

  double LastFireTime = 0.0;
};
