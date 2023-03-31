#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AWeapon;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
  static FName CameraComponentName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	FName SocketToAttachCameraTo = FName("head");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
  FName SocketToAttachWeaponTo = FName("hand_r");

  FORCEINLINE AWeapon* GetWeapon() const { return Weapon; }
  FORCEINLINE UCameraComponent* GetCameraComponent() const { return FPCameraComponent; }
	
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void StartShooting(const FInputActionValue& Value);
	virtual void StopShooting(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void EquipWeapon(AWeapon* InWeapon);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	AWeapon* Weapon;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
  TObjectPtr<UCameraComponent> FPCameraComponent;
};
