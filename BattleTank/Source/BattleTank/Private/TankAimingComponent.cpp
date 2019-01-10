// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
  Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

  if (UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutProjectileLaunchVelocity,
        StartLocation,
        HitLocation,
        ProjectileLaunchSpeed,
        false,
        0.0,
        0.0,
        ESuggestProjVelocityTraceOption::DoNotTrace
      )
    )
  {
    auto AimDirection = OutProjectileLaunchVelocity.GetSafeNormal();
    auto TankName = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *TankName, *AimDirection.ToString());
  }
}
