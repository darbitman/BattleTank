// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declarations:
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
    // Start the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world
    void AimTowardsCrosshair();

    // return an OUT paramter, true if hit landscape
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;

    bool GetLookDirection(const FVector2D& ScreenLocation, FVector& OutLookDirection) const;

    bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;

    UPROPERTY(EditDefaultsOnly)
    float CrosshairXLocation = 0.5f;

    UPROPERTY(EditDefaultsOnly)
    float CrosshairYLocation = 0.33333f;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0f; // 10km
};
