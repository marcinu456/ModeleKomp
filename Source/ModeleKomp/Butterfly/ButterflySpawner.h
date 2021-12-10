// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButterflyActor.h"
#include "GameFramework/Actor.h"
#include "ButterflySpawner.generated.h"

UCLASS()
class MODELEKOMP_API AButterflySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButterflySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
	int32 numberOfButterfly = 4;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AButterflyActor*> ButterflyActors;

	/** Class for cell. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<AButterflyActor> ButterflyActor;

};
