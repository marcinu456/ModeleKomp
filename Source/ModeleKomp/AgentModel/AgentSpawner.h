// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantAgent.h"
#include "RabbitAgent.h"
#include "WolfAgent.h"
#include "GameFramework/Actor.h"
#include "AgentSpawner.generated.h"

UCLASS()
class MODELEKOMP_API AAgentSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgentSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	const double SIZE = 10;

	const size_t PLANT_COUNT = 8;
	const size_t PLANT_MAX_HP = 240;
	const size_t PLANT_REPRODUCE_TIME = 30;
	const size_t PLANT_REPRODUCE_COUNT = 8;

	const size_t RABBIT_COUNT = 2;
	const size_t RABBIT_MAX_HP = 300;
	const size_t RABBIT_MAX_HUNGRY_HP_LEVEL = 150;
	const double RABBIT_VELOCITY = 2.5;

	const size_t WOLF_COUNT = 4;
	const size_t WOLF_MAX_HP = 500;
	const size_t WOLF_MAX_HUNGRY_HP_LEVEL = 150;
	const double WOLF_VELOCITY = 2;


	//TArray<APlantAgent*> Plants;
	//TArray<ARabbitAgent*> Rabbits;
	//TArray<AWolfAgent*> Wolfes;


	/** Class for cell. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<APlantAgent> PlantActor;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<ARabbitAgent> RabbitActor;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<AWolfAgent> WolfActor;

	template <typename ArrayClass, typename SubClass, class T>
	void SpawnActors(ArrayClass arrayClass, SubClass subClass, T clasa);

	size_t iter = 0;

};


