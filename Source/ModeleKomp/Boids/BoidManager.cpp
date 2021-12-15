// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidManager.h"

// Sets default values
ABoidManager::ABoidManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoidManager::BeginPlay()
{
	Super::BeginPlay();

	//for (int32 i = 0; i < AmountOfThreads; i++) {
	//	Runnables.Add(new FBoidCalculationWorker());
	//}
	InitializationDone = true;
}

void ABoidManager::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	//for (FBoidCalculationWorker* Runnable : Runnables) {
	//	Runnable->EnsureCompletion();
	//	delete Runnable;
	//}
}

void ABoidManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!Active) {
		return;
	}


	//if (InitializationDone && BoidsToDistributeToThreads.Num() != 0) {
	//	for (ABoid* Boid : BoidsToDistributeToThreads) {
	//		AddBoidToThread(Boid);
	//	}
	//	BoidsToDistributeToThreads.Empty();
	//}
	
	if (ManagedBoids.Num() != 0) {
		// Move boids forward each tick
		for (ABoid* Boid : ManagedBoids) {
			Boid->CalculateBoidRotation();
			Boid->UpdateBoidRotation(DeltaTime);
			Boid->CalculateBoidPosition(DeltaTime);
			Boid->UpdateBoidPosition();
		}
	}
}

void ABoidManager::AddManagedBoid(ABoid* Boid) {
	ManagedBoids.AddUnique(Boid);
	// Add Boid to list to be distributed to threads
	//BoidsToDistributeToThreads.Add(Boid);
	UE_LOG(LogTemp, Log, TEXT("Start managing %s"), *Boid->GetName());
}

void ABoidManager::RemoveManagedBoid(ABoid* Boid) {
	ManagedBoids.Remove(Boid);
	UE_LOG(LogTemp, Log, TEXT("Stop managing %s"), *Boid->GetName());
}

//void ABoidManager::AddBoidToThread(ABoid* Boid) {
//	int32 LeastManagedBoids = INT_MAX;
//	FBoidCalculationWorker* RunnableWithLeastBoids = nullptr;
//	for (FBoidCalculationWorker* Runnable : Runnables) {
//		int32 ManageBoidsCount = Runnable->ManagedBoidsCount();
//		if (ManageBoidsCount < LeastManagedBoids) {
//			LeastManagedBoids = ManageBoidsCount;
//			RunnableWithLeastBoids = Runnable;
//		}
//	}
//	if (RunnableWithLeastBoids) {
//		RunnableWithLeastBoids->AddBoid(Boid);
//	}
//}

