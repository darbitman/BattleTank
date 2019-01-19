// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
  auto ControlledTank = GetPawn();
  auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

  if (!ensure(PlayerTank && ControlledTank && AimingComponent)) { return; }

  // Move towards the player
  MoveToActor(PlayerTank, AcceptanceRadius);  // TODO check radius units

  // aim towards the player
  AimingComponent->AimAt(PlayerTank->GetActorLocation());

  // Fire projectile
  AimingComponent->Fire();  // TODO limit firing rate
}
