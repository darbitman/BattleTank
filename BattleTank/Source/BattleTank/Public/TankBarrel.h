// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  // -1.0 is max downward speed, +1.0 is max upward speed
  void Elevate(float RelativeSpeed);

private:
  UPROPERTY(EditAnywhere, Category = Setup)
  float MaxDegreesPerSecond = 10.0f;

  UPROPERTY(EditAnywhere, Category = Setup)
  float MaxElevationDegrees = 40.0f;

  UPROPERTY(EditAnywhere, Category = Setup)
  float MinElevationDegrees = 0.0f;
};