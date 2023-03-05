#pragma once

#include "CoreMinimal.h"
#include "CharacterMovementInterface.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class APlayerCharacter;

struct FInputActionValue;

UCLASS()
class AFPSPlayerController : public APlayerController, public ICharacterMovementInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Getters")
	FVector2D GetViewPitchLimit() const { return ViewPitchLimit; }

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetViewPitchLimit(FVector2D InViewPitchLimit) { ViewPitchLimit = InViewPitchLimit; }

	AFPSPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void SetupInputComponent() override;

	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;
	virtual void StartJump(const FInputActionValue& Value) override;
	virtual void StopJump(const FInputActionValue& Value) override;
	virtual void StartAttack(const FInputActionValue& Value) override;
  virtual void StopAttack(const FInputActionValue& Value) override;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
  TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
  TObjectPtr<UInputAction> AttackInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Camera Manager")
  FVector2D ViewPitchLimit = FVector2D(-45.0f, 45.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Input|Context")
  TObjectPtr<UInputMappingContext> DefaultInputContext;

	APlayerCharacter* GetPlayerCharacter() const;
};
