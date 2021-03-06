// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgentBase.h"
#include "WolfAgent.generated.h"

/**
 * 
 */
UCLASS()
class MODELEKOMP_API AWolfAgent : public AAgentBase
{
	GENERATED_BODY()

public:
	AWolfAgent();

	virtual void Tick(float DeltaTime) override;

private:
	/** called when something enters the sphere component */
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/** called when something leaves the sphere component */
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Move() override;

	class ARabbitAgent* atractorRabbit;
	AWolfAgent* atractorWolf;

	const size_t WOLF_COUNT = 4;
	const size_t WOLF_MAX_HP = 500;
	const size_t WOLF_MAX_HUNGRY_HP_LEVEL = 150;
	const double WOLF_VELOCITY = 2;
	const double WOLF_REPRODUCE_COUNT = 2;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<AWolfAgent> WolfActor;
};
