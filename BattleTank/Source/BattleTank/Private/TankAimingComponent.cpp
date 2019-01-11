// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;  // TODO should this tick

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileLaunchSpeed)
{
  //auto OurTankName = GetOwner()->GetName();
  //auto BarrelLocation = Barrel->GetComponentLocation().ToString();
  //UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);

  if (Barrel == nullptr) { return; }

  FVector OutProjectileLaunchVelocity(0);
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

  // Calculate the OutProjectileLaunchVelocity
  bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
    this,
    OutProjectileLaunchVelocity,
    StartLocation,
    HitLocation,
    ProjectileLaunchSpeed,
    false,
    0.0,
    0.0,
    ESuggestProjVelocityTraceOption::DoNotTrace
  );
  if (bHaveAimSolution && HitLocation != FVector(0.0f))
  {
    auto AimDirection = OutProjectileLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
  }
  else
  {
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution NOT found"), Time);
  }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  // Compute delta between current barrel rotation and AimDirection
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(5);
}