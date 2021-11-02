// Fill out your copyright notice in the Description page of Project Settings.


#include "Penduluy.h"

// Sets default values
APenduluy::APenduluy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstColumn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstColumn"));
	FirstColumn->SetupAttachment(GetRootComponent());
	FirstColumn->SetCollisionProfileName("NoCollision");

	SecondColumn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondColumn"));
	SecondColumn->SetupAttachment(FirstColumn);
	SecondColumn->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void APenduluy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APenduluy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

