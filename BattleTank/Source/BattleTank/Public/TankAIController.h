// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaTime) override;
  
private:
  // How close can the AI tank get
  float AcceptanceRadius = 3000.0f; // 30m
};
