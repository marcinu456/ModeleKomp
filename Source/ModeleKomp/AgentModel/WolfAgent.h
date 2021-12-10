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


	/** called when something enters the sphere component */
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/** called when something leaves the sphere component */
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
