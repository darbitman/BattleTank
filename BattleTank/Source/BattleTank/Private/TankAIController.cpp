// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
  auto PlayerTank = GetPlayerTank();
  if (!PlayerTank)
  {
    UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank"));
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *(PlayerTank->GetName()));
  }
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  if (GetPlayerTank())
  {
    // TODO Move towards the player

    // TODO aim towards the player
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

    // TODO Fire if ready
  }
}

ATank* ATankAIController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
  auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if (PlayerPawn == nullptr) { return nullptr; }
  return Cast<ATank>(PlayerPawn);
}
