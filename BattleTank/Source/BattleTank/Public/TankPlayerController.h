// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

private:
  ATank* GetControlledTank() const;

  // Start the tank moving the barrel so that a shot would hit where
  // the crosshair intersects the world
  void AimTowardsCrosshair();

  // return an OUT paramter, true if hit landscape
  bool GetSightRayHitLocation(FVector& OutHitLocation) const;

  bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;

  UPROPERTY(EditAnywhere)
  float CrosshairXLocation = 0.5f;

  UPROPERTY(EditAnywhere)
  float CrosshairYLocation = 0.33333f;
};
