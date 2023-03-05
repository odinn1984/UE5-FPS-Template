#include "Weapons/Weapon.h"
#include "Components/SkeletalMeshComponent.h"

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

  Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

  if (GetMesh())
  {
    SetRootComponent(GetMesh());
  }
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeapon::CanShoot() const
{
  return !bIsFiring && bCanFireAgain && GetWorld()->GetTimerManager().GetTimerRemaining(RapidFireCooldown) <= 0.0f;
}

void AWeapon::StartShooting()
{
  if (!CanShoot())
  {
    return;
  }

  bIsFiring = true;
  bCanFireAgain = bIsRapidFireWeapon;

  Shoot();

  OnStartShooting.Broadcast();
}

void AWeapon::StopShooting()
{
  bIsFiring = false;
  bCanFireAgain = true;
  
  OnStopShooting.Broadcast();
}

void AWeapon::AddAmmo(int Amount)
{
  CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	FireRate = 1.0f / BulletsPerSecond;
	CurrentAmmo = MaxAmmo;
}

void AWeapon::ShootAction()
{
}

void AWeapon::OnFireCooldown()
{
  bIsFiring = false;
  bCanFireAgain = true;
}

void AWeapon::Shoot()
{
  if (CurrentAmmo > 0)
  {
    CurrentAmmo--;
    
    ShootAction();
    GetWorld()->GetTimerManager().SetTimer(RapidFireCooldown, this, &AWeapon::OnFireCooldown, FireRate);

    OnShoot.Broadcast();
  }
  else
  {
    OnOutOfAmmo.Broadcast();
  }
}
