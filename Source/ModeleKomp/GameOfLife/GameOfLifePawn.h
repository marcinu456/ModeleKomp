// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameOfLifePawn.generated.h"

UCLASS()
class MODELEKOMP_API AGameOfLifePawn : public APawn
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SwitchMode();
	void SpeedUp();
	void SlowDown();
	void Reset();
};
