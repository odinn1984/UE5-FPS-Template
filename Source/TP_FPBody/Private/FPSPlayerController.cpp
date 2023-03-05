#include "FPSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"

AFPSPlayerController::AFPSPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  MoveInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Move.IA_Move'"));
  LookInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Look.IA_Look'"));
  JumpInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Jump.IA_Jump'"));
  AttackInputAction = LoadObject<UInputAction>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputAction'/Game/FPBody/Inputs/Actions/IA_Attack.IA_Attack'"));

  DefaultInputContext = LoadObject<UInputMappingContext>(
    nullptr,
    TEXT("/Script/EnhancedInput.InputMappingContext'/Game/FPBody/Inputs/IMC_DefaultPlayer.IMC_DefaultPlayer'"));
}

void AFPSPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();

  UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
  UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

  check(PlayerEnhancedInputComponent != nullptr);
  check(Subsystem != nullptr);

  Subsystem->ClearAllMappings();
  Subsystem->AddMappingContext(DefaultInputContext, 0);

  if (MoveInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::Move);
  }

  if (LookInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::Look);
  }

  if (JumpInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::StartJump);
    PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &AFPSPlayerController::StopJump);
  }

  if (AttackInputAction)
  {
    PlayerEnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Triggered, this, &AFPSPlayerController::StartAttack);
    PlayerEnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Completed, this, &AFPSPlayerController::StopAttack);
  }
}

void AFPSPlayerController::Move(const FInputActionValue& Value)
{
  const FVector2D MovementVector = Value.Get<FVector2D>();

  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->Move(Value);
  }
}

void AFPSPlayerController::Look(const FInputActionValue& Value)
{
  const FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->Look(Value);
  }
}

void AFPSPlayerController::StartJump(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->Jump();
  }
}

void AFPSPlayerController::StopJump(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->StopJumping();
  }
}

void AFPSPlayerController::StartAttack(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->StartShooting(Value);
  }
}

void AFPSPlayerController::StopAttack(const FInputActionValue& Value)
{
  if (APlayerCharacter* player = GetPlayerCharacter())
  {
    player->StopShooting(Value);
  }
}

void AFPSPlayerController::BeginPlay()
{
  Super::BeginPlay();

  PlayerCameraManager->ViewPitchMin = ViewPitchLimit.X;
  PlayerCameraManager->ViewPitchMax = ViewPitchLimit.Y;
}

APlayerCharacter* AFPSPlayerController::GetPlayerCharacter() const
{
  return Cast<APlayerCharacter>(GetPawn());
}

