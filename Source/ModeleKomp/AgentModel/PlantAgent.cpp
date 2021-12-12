// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantAgent.h"

APlantAgent::APlantAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void APlantAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (hp != 0) {
		hp--;
	}
	else {
		Destroy();
	}
}
