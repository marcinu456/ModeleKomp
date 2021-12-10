// Fill out your copyright notice in the Description page of Project Settings.


#include "ButterflyActor.h"

// Sets default values
AButterflyActor::AButterflyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CellRootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AButterflyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButterflyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaTime = 0.002;
	auto position = GetActorLocation();
	
	position.X = position.X + 10.0 * (position.Y - position.X) * DeltaTime;
	position.Y = position.Y + (-position.X * position.Z + 28.0 * position.X - position.Y) * DeltaTime;
	position.Z = position.Z + (position.X * position.Y - (8.0 / 3.0) * position.Z) * DeltaTime;

	SetActorLocation(position);

	UE_LOG(LogTemp, Warning, TEXT("X= %f, Y= %f, Z= %f"), position.X, position.Y, position.Z );

}

