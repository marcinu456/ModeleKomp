// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidSpawner.h"

#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABoidSpawner::ABoidSpawner() {
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneComponent"));
	SetRootComponent(SceneComponent);

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(FName("BillboardComponent"));
	BillboardComponent->SetupAttachment(SceneComponent);
}

void ABoidSpawner::BeginPlay() {
	Super::BeginPlay();

	// only load config in shipping builds else use value specifed in the editor
#if UE_BUILD_SHIPPING 
	ReloadConfig(ABoidSpawner::StaticClass());
#endif

	if (!Active) {
		return;
	}

	if (ClassToSpawn) {
		for (int index = 0; index < SpawnCount; index++) {
			FVector SpawnLocation = UKismetMathLibrary::RandomUnitVector() * SpawnRadius + GetActorLocation();
			GetWorld()->SpawnActor<ABoid>(ClassToSpawn, SpawnLocation, RandomSpawnRotation());
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Class of objects to spawn is missing"));
	}
}

/* also see UKismetMathLibrary::RandomRotator */
FRotator ABoidSpawner::RandomSpawnRotation() {
	FRotator RRot;
	RRot.Yaw = RandomYaw ? FMath::FRand() * 360.f : 0;
	RRot.Pitch = RandomPitch ? FMath::FRand() * 360.f : 0;
	RRot.Roll = RandomRoll ? FMath::FRand() * 360.f : 0;
	return RRot;
}
