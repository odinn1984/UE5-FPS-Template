#include "Weapons/Projectile.h"
#include "PlayerCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

FName AProjectile::CapsuleComponentName = TEXT("Capsule Component");
FName AProjectile::StaticMeshComponentName = TEXT("Mesh");
FName AProjectile::ProjectileMovementComponentName = TEXT("Projectile Movement Component");

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

  CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(AProjectile::CapsuleComponentName);

  if (GetCapsule())
  {
    GetCapsule()->InitCapsuleSize(25.0f, 25.0f);
    GetCapsule()->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
    GetCapsule()->BodyInstance.SetCollisionProfileName("Projectile");
    GetCapsule()->CanCharacterStepUpOn = ECB_No;

    SetRootComponent(GetCapsule());
  }

  Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(AProjectile::StaticMeshComponentName);

  if (GetMesh())
  {
    GetMesh()->SetupAttachment(GetRootComponent());
    GetMesh()->SetWorldScale3D(FVector(0.125f, 0.125f, 0.125f));

    UStaticMesh* DefaultMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));

    if (DefaultMesh)
    {
      GetMesh()->SetStaticMesh(DefaultMesh);
    }
  }

  ProjectileMovementComponent = CreateOptionalDefaultSubobject<UProjectileMovementComponent>(AProjectile::ProjectileMovementComponentName);

  if (GetMovementComponent())
  {
    GetMovementComponent()->SetUpdatedComponent(GetRootComponent());
    GetMovementComponent()->InitialSpeed = 5000.0f;
    GetMovementComponent()->MaxSpeed = 3000.0f;
    GetMovementComponent()->bShouldBounce = true;
    GetMovementComponent()->bRotationFollowsVelocity = true;
  }

  InitialLifeSpan = 5.0f;
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnTargetHit_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  if (!OtherActor || !OtherActor || !OtherComp || !GetWorld())
  {
    return;
  }

  if (OtherComp->IsSimulatingPhysics())
  {
    OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
  }

  UGameplayStatics::ApplyDamage(
    OtherActor,
    DamageAmountOnHit,
    UGameplayStatics::GetPlayerController(GetWorld(), 0),
    UGameplayStatics::GetPlayerCharacter(GetWorld(), 0),
    UDamageType::StaticClass()
  );

  OnHit.Broadcast(OtherActor, DamageAmountOnHit);
}

void AProjectile::BeginPlay()
{
  Super::BeginPlay();

  if (GetCapsule())
  {
    GetCapsule()->OnComponentHit.AddDynamic(this, &AProjectile::OnTargetHit);
  }
}

