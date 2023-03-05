#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterMovementInterface.generated.h"

struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterMovementInterface : public UInterface
{
	GENERATED_BODY()
};

class ICharacterMovementInterface
{
	GENERATED_BODY()

public:
	virtual void Move(const FInputActionValue& Value) = 0;
	virtual void Look(const FInputActionValue& Value) = 0;
	virtual void StartJump(const FInputActionValue& Value) = 0;
	virtual void StopJump(const FInputActionValue& Value) = 0;
	virtual void StartAttack(const FInputActionValue& Value) = 0;
	virtual void StopAttack(const FInputActionValue& Value) = 0;
};
