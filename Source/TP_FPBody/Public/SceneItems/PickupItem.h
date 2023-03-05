#pragma once

#include "CoreMinimal.h"
#include "SceneItems/SceneItem.h"
#include "PickupItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemPickupSignature, const AActor*, InteractingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnableToPickupItemSignature, const AActor*, InteractingActor);

UCLASS(Abstract)
class TP_FPBODY_API APickupItem : public ASceneItem
{
	GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FOnItemPickupSignature OnItemPickup;

  UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FOnUnableToPickupItemSignature OnUnableToPickupItem;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
  bool bEnablePhysicsInRuntime = false;

  virtual bool CanPickup(AActor* InteractingActor);
  virtual void PickupItem(AActor* InteractingActor);
  virtual void UnableToPickupItem(AActor* InteractingActor);
  
  virtual void OnActorBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
  virtual void BeginPlay() override;
  
};
