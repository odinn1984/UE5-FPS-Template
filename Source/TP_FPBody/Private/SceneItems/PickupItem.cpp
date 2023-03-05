#include "SceneItems/PickupItem.h"
#include "Components/CapsuleComponent.h"

bool APickupItem::CanPickup(AActor* InteractingActor)
{
  return false;
}

void APickupItem::PickupItem(AActor* InteractingActor)
{
  OnItemPickup.Broadcast(InteractingActor);
}

void APickupItem::UnableToPickupItem(AActor* InteractingActor)
{
  OnUnableToPickupItem.Broadcast(InteractingActor);
}

void APickupItem::OnActorBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  Super::OnActorBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

  if (CanPickup(OtherActor))
  {
    PickupItem(OtherActor);

    if (GetCapsule() && GetMesh())
    {
      GetMesh()->SetVisibility(false);
    }

    if (GetCapsule())
    {
      GetCapsule()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
      GetCapsule()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    }

    bShouldDestroyOnEndOverlap = true;
  }
  else
  {
    UnableToPickupItem(OtherActor);
  }
}

void APickupItem::BeginPlay()
{
  Super::BeginPlay();

  if (bEnablePhysicsInRuntime && GetCapsule())
  {
    GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsule()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    GetCapsule()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    GetCapsule()->SetSimulatePhysics(true);
  }
}
