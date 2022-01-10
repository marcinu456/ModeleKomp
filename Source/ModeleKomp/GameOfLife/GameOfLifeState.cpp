// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOfLifeState.h"

#include "Kismet/GameplayStatics.h"

void AGameOfLifeState::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Rabbits;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridActor3D::StaticClass(), Rabbits);


	for (auto& Rabbit : Rabbits)
	{
		GridActors.Add(Cast<AGridActor3D>(Rabbit));
	}


	/*for (FTransform T : Transforms) {
		GridActors.Add(GetWorld()->SpawnActor<AGridActor3D>(GridActor, T));
	}*/

	EditMode = true;
}

void AGameOfLifeState::SetEditMode(const bool Editing) {
	if (Editing) {
		for (AGridActor3D* Grid : GridActors) {
			Grid->ToEditMode();
		}
	}
	else {
		for (AGridActor3D* Grid : GridActors) {
			Grid->ToPlayMode();
		}
	}
	EditMode = Editing;
}

void AGameOfLifeState::StartTimers() {
	for (AGridActor3D* Grid : GridActors) {
		Grid->StartTimer();
	}
}

void AGameOfLifeState::ClearTimers() {
	for (AGridActor3D* Grid : GridActors) {
		Grid->ClearTimer();
	}
}

void AGameOfLifeState::Reset() {
	for (AGridActor3D* Grid : GridActors) {
		Grid->Reset();
	}
	SetEditMode(true);
}

void AGameOfLifeState::SpeedUp() {
	if (AdvanceTime >= 0.2f) {
		AdvanceTime -= 0.1f;
	}
}

void AGameOfLifeState::SlowDown() {
	if (AdvanceTime <= 9.9f) {
		AdvanceTime += 0.1f;
	}
}