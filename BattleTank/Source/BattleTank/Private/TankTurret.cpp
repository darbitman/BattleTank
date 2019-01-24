// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    // rotate the turret the right amound this frame
    // Given a max rotation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
    auto YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Yaw = RelativeRotation.Yaw + YawChange;

    SetRelativeRotation(FRotator(0.0f, Yaw, 0.0f));
}