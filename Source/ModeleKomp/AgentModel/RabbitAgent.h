// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgentBase.h"
#include "RabbitAgent.generated.h"

/**
 * 
 */
UCLASS()
class MODELEKOMP_API ARabbitAgent : public AAgentBase
{
	GENERATED_BODY()
public:
	ARabbitAgent();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Move() override;

	const size_t RABBIT_COUNT = 8;
	const size_t RABBIT_MAX_HP = 300;
	const size_t RABBIT_MAX_HUNGRY_HP_LEVEL = 150;
	const double RABBIT_VELOCITY = 2.5;
	const double RABBIT_REPRODUCE_COUNT = 2;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<ARabbitAgent> RabbitActor;

	class APlantAgent* atractorPlant;
	ARabbitAgent* atractorRabbit;


	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
