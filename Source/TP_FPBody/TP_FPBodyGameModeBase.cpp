// Fill out your copyright notice in the Description page of Project Settings.

#include "TP_FPBodyGameModeBase.h"

#include "PlayerCharacter.h"
#include "FPSPlayerController.h"

ATP_FPBodyGameModeBase::ATP_FPBodyGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
  DefaultPawnClass = APlayerCharacter::StaticClass();
  PlayerControllerClass = AFPSPlayerController::StaticClass();
}
