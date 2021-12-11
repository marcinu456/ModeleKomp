// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantAgent.h"
#include "RabbitAgent.h"
#include "WolfAgent.h"
#include "GameFramework/GameModeBase.h"
#include "AgentGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MODELEKOMP_API AAgentGameMode : public AGameModeBase
{
	GENERATED_BODY()


	TArray<APlantAgent*> Plants;
	TArray<ARabbitAgent*> Rabbits;
	TArray<AWolfAgent*> Wolfes;


	void AddToPlants(APlantAgent* Plant) { Plants.Add(Plant); }

};
