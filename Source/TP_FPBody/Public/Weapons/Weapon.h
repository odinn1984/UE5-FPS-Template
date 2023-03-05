#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartShootSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopShootSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfAmmoSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShootSignature);

class USkeletalMeshComponent;

UCLASS(Abstract)
class TP_FPBODY_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FOnStartShootSignature OnStartShooting;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FOnStopShootSignature OnStopShooting;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnOutOfAmmoSignature OnOutOfAmmo;

  UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FOnOutOfAmmoSignature OnShoot;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (ClampMin = "0"))
  int MaxAmmo = 100;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (ClampMin = "0"))
  int CurrentAmmo = MaxAmmo;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (ClampMin = "0"))
  int DamageOnHit = 10;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (ClampMin = "0.0"))
  float BulletsPerSecond = 4.0f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
  bool bIsRapidFireWeapon = false;

  FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }

  UFUNCTION(BlueprintCallable, Category = "Setters")
  FORCEINLINE void SetDamageOnHit(int InDamageOnHit) { DamageOnHit = FMath::Max(0.0f, InDamageOnHit); }

  UFUNCTION(BlueprintCallable, Category = "Setters")
  FORCEINLINE void SetBulletsPerSecond(float InBulletsPerSecond) { BulletsPerSecond = FMath::Max(0.0f, InBulletsPerSecond); }

  UFUNCTION(BlueprintCallable, Category = "Setters")
  FORCEINLINE void SetMaxAmmo(int InAmount) { MaxAmmo = FMath::Max(0, InAmount); };

  AWeapon(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

  UFUNCTION(BlueprintCallable, Category = "Ammo")
  bool IsAtMaxAmmo() const { return MaxAmmo == CurrentAmmo; }

  UFUNCTION(BlueprintCallable, Category = "Ammo")
  bool CanShoot() const;

	virtual void StartShooting();
	virtual void StopShooting();

  UFUNCTION(BlueprintCallable, Category = "Ammo")
	virtual void AddAmmo(int Amount);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
  TObjectPtr<USkeletalMeshComponent> Mesh;

  virtual void BeginPlay() override;
  virtual void ShootAction();
  virtual void OnFireCooldown();

private:
  FTimerHandle RapidFireCooldown;

  bool bIsFiring = false;
  bool bCanFireAgain = true;
  float FireRate = 1.0f / BulletsPerSecond;

  virtual void Shoot();
};
