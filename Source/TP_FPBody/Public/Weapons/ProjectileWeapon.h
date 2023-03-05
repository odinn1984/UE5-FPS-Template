#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "ProjectileWeapon.generated.h"

class AProjectile;

UCLASS()
class TP_FPBODY_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
  FVector MuzzleOffset = FVector(200.0f, 0.0f, 0.0f);

	TSubclassOf<AProjectile> GetProjectileClass() const { return ProjectileClass; }

	AProjectileWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void ShootAction() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|Context", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;

};
