// Fill out your copyright notice in the Description page of Project Settings.


#include "RabbitAgent.h"

ARabbitAgent::ARabbitAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}
