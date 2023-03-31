#include "SceneItems/SceneItem.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

FName ASceneItem::CapsuleComponentName = TEXT("Capsule Component");
FName ASceneItem::StaticMeshComponentName = TEXT("Mesh");

ASceneItem::ASceneItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(ASceneItem::CapsuleComponentName);

	if (GetCapsule()) 
	{
		GetCapsule()->InitCapsuleSize(18.0f, 18.0f);
		GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		GetCapsule()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		GetCapsule()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		GetCapsule()->SetGenerateOverlapEvents(true);

		SetRootComponent(GetCapsule());
	}

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(ASceneItem::StaticMeshComponentName);

	if (GetMesh())
	{
		GetMesh()->SetupAttachment(GetRootComponent());
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
}

void ASceneItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldRotate)
	{
		AddActorLocalRotation(RotationSpeed);
	}
}

void ASceneItem::OnActorBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnBeginOverlap.Broadcast(OtherActor);
}

void ASceneItem::OnActorEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnEndOverlap.Broadcast(OtherActor);

	if (bShouldDestroyOnEndOverlap)
	{
		Destroy();
	}
}

void ASceneItem::BeginPlay()
{
	Super::BeginPlay();

	if (GetCapsule())
	{
		GetCapsule()->OnComponentBeginOverlap.AddDynamic(this, &ASceneItem::OnActorBeginOverlap);
		GetCapsule()->OnComponentEndOverlap.AddDynamic(this, &ASceneItem::OnActorEndOverlap);
	}
}
 