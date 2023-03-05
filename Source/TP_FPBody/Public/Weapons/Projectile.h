#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileOnHitSignature, const AActor*, Actor, const int, DamageOnHit);

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class TP_FPBODY_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
  static FName CapsuleComponentName;
  static FName StaticMeshComponentName;
  static FName ProjectileMovementComponentName;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FProjectileOnHitSignature OnHit;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision", meta = (ClampMin = "0"))
  int DamageAmountOnHit = 10;

	AProjectile();
  
  FORCEINLINE UCapsuleComponent* GetCapsule() const { return CapsuleComponent; }
  FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
  FORCEINLINE UProjectileMovementComponent* GetMovementComponent() const { return ProjectileMovementComponent; }

	virtual void Tick(float DeltaTime) override;

  UFUNCTION(BlueprintNativeEvent)
  void OnTargetHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  virtual void OnTargetHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
  TObjectPtr<UCapsuleComponent> CapsuleComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
  TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
  TObjectPtr<UStaticMeshComponent> Mesh;

};
