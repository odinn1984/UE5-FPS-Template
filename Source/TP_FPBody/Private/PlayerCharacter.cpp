#include "PlayerCharacter.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/Weapon.h"

FName APlayerCharacter::CameraComponentName(TEXT("First Person Camera"));

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	FPCameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(APlayerCharacter::CameraComponentName);

	if (GetCameraComponent())
	{
		GetCameraComponent()->SetRelativeLocation(FVector(0.0f, 20.0f, 0.0f));
		GetCameraComponent()->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
		GetCameraComponent()->bUsePawnControlRotation = true;
	}

	if(GetMesh())
	{
		TObjectPtr<USkeletalMesh> DefaultMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
		TObjectPtr<UAnimBlueprint> DefaultAnimationBP = LoadObject<UAnimBlueprint>(nullptr, TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn'"));

		GetMesh()->SetupAttachment(GetCapsuleComponent());

		if (DefaultMesh)
		{
			GetMesh()->SetSkeletalMesh(DefaultMesh);
			GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
			GetMesh()->SetWorldScale3D(FVector(1.35f, 1.35f, 1.35f));

			GetCameraComponent()->SetupAttachment(GetMesh(), SocketToAttachCameraTo);
		}
		else
		{
			GetCameraComponent()->SetupAttachment(GetCapsuleComponent());
		}

		if (DefaultAnimationBP)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(DefaultAnimationBP->GetAnimBlueprintGeneratedClass());
		}
	}

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	}

	SetReplicates(true);
	SetReplicateMovement(true);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::StartShooting(const FInputActionValue& Value)
{
	if (GetWeapon())
	{
		GetWeapon()->StartShooting();
	}
}

void APlayerCharacter::StopShooting(const FInputActionValue& Value)
{
	if (GetWeapon())
	{
		GetWeapon()->StopShooting();
	}
}

void APlayerCharacter::EquipWeapon(AWeapon* InWeapon)
{
	if (!InWeapon)
	{
		return;
	}

	Weapon = InWeapon;
	
	if (GetWeapon()->GetMesh() && GetMesh())
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

		GetWeapon()->GetMesh()->AttachToComponent(
			GetMesh(), 
			AttachmentRules,
			SocketToAttachWeaponTo
		);

		GetWeapon()->SetActorRelativeRotation(FRotator(10.0f, 70.0f, 10.0f));
	}

	GetWeapon()->SetOwner(this);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
