#include "Weapons/ProjectileWeapon.h"
#include "PlayerCharacter.h"
#include "Weapons/Projectile.h"

AProjectileWeapon::AProjectileWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  if (GetMesh())
  {
    USkeletalMesh* DefaultMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

    if (DefaultMesh)
    {
      GetMesh()->SetSkeletalMesh(DefaultMesh);
    }
  }

  bIsRapidFireWeapon = true;
	ProjectileClass = AProjectile::StaticClass();
}

void AProjectileWeapon::ShootAction()
{
  Super::ShootAction();

	if (!GetOwner() || !GetProjectileClass() || !GetWorld())
	{
		return;
	}

	const APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());

	if (!Character)
	{
		return;
	}
	
	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());

	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor<AProjectile>(GetProjectileClass(), SpawnLocation, SpawnRotation, ActorSpawnParams);
}
