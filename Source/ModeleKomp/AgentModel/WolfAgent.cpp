// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfAgent.h"

#include "RabbitAgent.h"
#include "Components/SphereComponent.h"

AWolfAgent::AWolfAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);


	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Sphere1->InitSphereRadius(100.0f);
	Sphere1->SetupAttachment(RootComponent);

	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &AWolfAgent::OnOverlapBegin);       // set up a notification for when this component overlaps something
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &AWolfAgent::OnOverlapEnd);

}

void AWolfAgent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	auto castActor = Cast<ARabbitAgent>(OtherActor);

	if(castActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Some warning castActor"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Some warning OtherActor"));
	}
}

void AWolfAgent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}
