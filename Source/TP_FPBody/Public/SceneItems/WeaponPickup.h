#pragma once

#include "CoreMinimal.h"
#include "SceneItems/PickupItem.h"
#include "WeaponPickup.generated.h"

class AWeapon;
class APlayerCharacter;

UCLASS()
class TP_FPBODY_API AWeaponPickup : public APickupItem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;

	AWeaponPickup(const FObjectInitializer& ObjectInitializer);

	virtual bool CanPickup(AActor* InteractingActor) override;
	virtual void PickupItem(AActor* InteractingActor) override;

protected:
	virtual APlayerCharacter* GetPlayerCharacter(AActor* InteractingActor) const;

};
