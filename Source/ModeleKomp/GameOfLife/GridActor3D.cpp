// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor3D.h"

#include "CellActor.h"
#include "GameOfLifeState.h"
#include "Kismet/GameplayStatics.h"

void AGridActor3D::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> Components;
	CellActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	const FVector BoxExtent = Components[0]->GetStaticMesh()->GetBounds().BoxExtent;
	const FVector Scale = Components[0]->GetRelativeTransform().GetScale3D();

	ensure(Components.Num() > 0);

	const float EffectiveBoxExtentX = BoxExtent.X * Scale.X + Offset;
	const float EffectiveBoxExtentY = BoxExtent.Y * Scale.Y + Offset;
	const float EffectiveBoxExtentZ = BoxExtent.Z * Scale.Z + Offset;
	const float XStep = EffectiveBoxExtentX * 2;
	const float YStep = EffectiveBoxExtentY * 2;
	const float ZStep = EffectiveBoxExtentZ * 2;
	const float BoardDeep = EffectiveBoxExtentX * 2 * Deep;
	const float BoardWidth = EffectiveBoxExtentY * 2 * Width;
	const float BoardHeight = EffectiveBoxExtentZ * 2 * Height;

	const FVector Origin = GetActorLocation();
	const FVector TopLeft(Origin.X - BoardDeep / 2 + EffectiveBoxExtentX, Origin.Y - BoardWidth / 2 + EffectiveBoxExtentY, Origin.Z + BoardHeight / 2 - EffectiveBoxExtentZ);

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				const FVector Loc(Origin.X + k * XStep, TopLeft.Y + j * YStep, TopLeft.Z - i * ZStep);
				ACellActor* const SpawnedActorRef = GetWorld()->SpawnActor<ACellActor>(CellActor, Loc, GetActorRotation()); //const pointer to non-const CellActor
				CellActors.Add(SpawnedActorRef);
			}
		}
	}
}

int AGridActor3D::CountAliveNeighbors(const int i, const int j) {
	int NumAliveNeighbors = 0;
	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			if (!(l == 0 && k == 0)) {
				const int effective_i = i + k;
				const int effective_j = j + l;
				if ((effective_i >= 0 && effective_i < Height) && (effective_j >= 0 && effective_j < Width)) {
					if (CellActors[effective_j + effective_i * Width]->GetAlive()) {
						NumAliveNeighbors++;
					}
				}
			}
		}
	}
	return NumAliveNeighbors;
}

void AGridActor3D::UpdateAliveNext(const int Index, const int NumAliveNeighbors) {
	const bool IsAlive = CellActors[Index]->GetAlive();
	if (IsAlive && (NumAliveNeighbors < 2))
	{
		CellActors[Index]->SetAliveNext(false);
	}
	else if (IsAlive && ((NumAliveNeighbors == 2) || (NumAliveNeighbors == 3)))
	{
		CellActors[Index]->SetAliveNext(true);
	}
	else if (IsAlive && (NumAliveNeighbors > 3))
	{
		CellActors[Index]->SetAliveNext(false);
	}
	else if (!IsAlive && (NumAliveNeighbors == 3))
	{
		CellActors[Index]->SetAliveNext(true);
	}
	else {
		CellActors[Index]->SetAliveNext(CellActors[Index]->GetAlive());
	}
}

void AGridActor3D::GenerateNext() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int NumAliveNeighbors = CountAliveNeighbors(i, j);
			UpdateAliveNext(j + i * Width, NumAliveNeighbors);
		}
	}
}

void AGridActor3D::UpdateNext() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			CellActors[Index]->Update();
		}
	}
}

void AGridActor3D::Advance() {
	UE_LOG(LogTemp, Warning, TEXT("advancing"));
	GenerateNext();
	UpdateNext();
}

void AGridActor3D::ToEditMode() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			CellActors[Index]->SetActorHiddenInGame(false);
		}
	}
}

void AGridActor3D::ToPlayMode() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int Index = j + i * Width;
			const bool IsAlive = CellActors[Index]->GetAlive();
			if (IsAlive) {
				CellActors[Index]->SetActorHiddenInGame(false);
			}
			else {
				CellActors[Index]->SetActorHiddenInGame(true);
			}
		}
	}
}

void AGridActor3D::StartTimer() {
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>(UGameplayStatics::GetGameState(GetWorld()));
	const float AdvanceTime = MyGameState->GetAdvanceTime();
	FTimerHandle AdvanceTimer;
	GetWorld()->GetTimerManager().SetTimer(AdvanceTimer, this, &AGridActor3D::Advance, AdvanceTime, true);
}

void AGridActor3D::ClearTimer() {
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AGridActor3D::Reset() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			CellActors[Index]->Reset();
			ClearTimer();
		}
	}
}
