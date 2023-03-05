#include "SceneItems/WeaponPickup.h"
#include "PlayerCharacter.h"
#include "Weapons/Weapon.h"
#include "Weapons/ProjectileWeapon.h"
#include "Components/StaticMeshComponent.h"

AWeaponPickup::AWeaponPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  if (GetMesh())
  {
    UStaticMesh* DefaultMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FPGunMesh.FPGunMesh'"));

    if (DefaultMesh)
    {
      GetMesh()->SetStaticMesh(DefaultMesh);
    }
  }

  bShouldRotate = true;
  WeaponClass = AProjectileWeapon::StaticClass();
}

bool AWeaponPickup::CanPickup(AActor* InteractingActor)
{
  return GetPlayerCharacter(InteractingActor) != nullptr;
}

void AWeaponPickup::PickupItem(AActor* InteractingActor)
{
  Super::PickupItem(InteractingActor);

  APlayerCharacter* player = GetPlayerCharacter(InteractingActor);

  if (player && GetWorld())
  {
    AWeapon* WeaponInstance = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FTransform::Identity);

    player->EquipWeapon(WeaponInstance);
  }
}

APlayerCharacter* AWeaponPickup::GetPlayerCharacter(AActor* InteractingActor) const
{
  return Cast<APlayerCharacter>(InteractingActor);
}