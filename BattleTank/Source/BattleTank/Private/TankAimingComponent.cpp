#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() : AimDirection(0.0f)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    if (RoundsLeft <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

EFiringState UTankAimingComponent::GetFireingState() const
{
    return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize LastFireTime to the moment the tank starts playing
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel)) { return; }

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
        AimDirection = OutProjectileLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards();
    }
}

void UTankAimingComponent::Fire()
{
    if (!ensure(Barrel)) { return; }
    if (!ensure(ProjectileBlueprint)) { return; }

    if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked)
    {
        // Spawn a projectile at the socket location on the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile"))
            );
        Projectile->LaunchProjectile(ProjectileLaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        RoundsLeft--;
    }
}

void UTankAimingComponent::MoveBarrelTowards()
{
    if (!ensure(Barrel && Turret)) { return; }

    // Compute delta between current barrel rotation and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    if (FMath::Abs(DeltaRotator.Yaw) < 180)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }

}

bool UTankAimingComponent::IsBarrelMoving() const
{
    if (!ensure(Barrel)) { return false; }
    auto BarrelForwardVector = Barrel->GetForwardVector().GetSafeNormal();
    return !BarrelForwardVector.Equals(AimDirection, 0.005);
}
