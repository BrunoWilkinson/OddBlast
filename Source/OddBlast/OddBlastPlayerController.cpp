// Fill out your copyright notice in the Description page of Project Settings.


#include "OddBlastPlayerController.h"

void AOddBlastPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	RestartLevel();
}
