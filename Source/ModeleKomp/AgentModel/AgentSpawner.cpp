// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentSpawner.h"

// Sets default values
AAgentSpawner::AAgentSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgentSpawner::BeginPlay()
{
	Super::BeginPlay();

	const FVector Origin = GetActorLocation();

	TArray<UStaticMeshComponent*> Components;
	PlantActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);
	

	for (size_t i = 0; i < PLANT_COUNT; i++)
	{
		const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y+ FMath::RandRange(-500, 500), Origin.Z);
		APlantAgent* const SpawnedActorRef = GetWorld()->SpawnActor<APlantAgent>(PlantActor, Loc, GetActorRotation());
		SpawnedActorRef->hp = PLANT_MAX_HP;
		Plants.Add(SpawnedActorRef);
	}


	RabbitActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);


	for (size_t i = 0; i < RABBIT_COUNT; i++)
	{
		const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
		auto const SpawnedActorRef = GetWorld()->SpawnActor<ARabbitAgent>(RabbitActor, Loc, GetActorRotation());
		SpawnedActorRef->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		Rabbits.Add(SpawnedActorRef);
	}


	WolfActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);


	for (size_t i = 0; i < WOLF_COUNT; i++)
	{
		const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
		auto const SpawnedActorRef = GetWorld()->SpawnActor<AWolfAgent>(WolfActor, Loc, GetActorRotation());
		SpawnedActorRef->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
		Wolfes.Add(SpawnedActorRef);
	}
}

// Called every frame
void AAgentSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (iter != -30) {
		iter = 0;
		// plant
		/*if (iter % PLANT_REPRODUCE_TIME == 0) {
			for (int i = 0; i < PLANT_REPRODUCE_COUNT; i++) {
				Plants.push_back(Plant(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PLANT_MAX_HP));
			}
		}*/



		for (int i = 0; i < Plants.Num(); i++) {
			auto plant = Plants[i];
			if (plant->hp != 0) {
				plant->hp--;
			}
			else {
				Plants.RemoveAt(i);
				i--;
				continue;
			}
		}

		// Rabbits

		/*if (Rabbits.size() == 0)
		{
			for (int i = 0; i < RABBIT_COUNT; i++) {
				Rabbits.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), RABBIT_MAX_HUNGRY_HP_LEVEL));
			}
		}*/

		//for (int i = 0; i < Rabbits.Num(); i++) {
		//	auto rabbit = Rabbits[i];
		//	if (rabbit->hp != 0) {
		//		rabbit->hp--;
		//	}
		//	else {
		//		Rabbits.RemoveAt(i);
		//		i--;
		//		continue;
		//	}
		//}
		//
		//for (int i = 0; i < Rabbits.Num(); i++) {
		//	auto rabbit = Rabbits[i];
		//
		//
		//	if (rabbit->hp <= RABBIT_MAX_HUNGRY_HP_LEVEL) {
		//		if (Plants.Num() > 0) {
		//			size_t atractorIndex = 0;
		//			auto atractor = Plants[atractorIndex]->GetActorLocation() - rabbit->GetActorLocation();
		//			float atractortDist = atractor.Size();// Plants[atractorIndex]->GetActorLocation(), rabbit->GetActorLocation());
		//			for (int j = 1; j < Plants.Num(); j++) {
		//				auto* plant = Plants[j];
		//				auto vec = plant->GetActorLocation() - rabbit->GetActorLocation();
		//				float dist = vec.Size();// FVector::Distance(plant->GetActorLocation(), rabbit->GetActorLocation());
		//				if (dist < atractortDist) {
		//					atractorIndex = j;
		//					atractor = vec;
		//					atractortDist = dist;
		//				}
		//			}
		//			UE_LOG(LogTemp, Warning, TEXT("atractor X=%f , Y=%f / atractortDist %f "), atractor.X, atractor.Y, atractortDist);
		//			rabbit->SetActorLocation(rabbit->GetActorLocation() + atractor / atractortDist * RABBIT_VELOCITY);
		//			UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
		//
		//			if ((rabbit->GetActorLocation() - Plants[atractorIndex]->GetActorLocation()).Size() < SIZE) {
		//				Plants.RemoveAt(atractorIndex);
		//				rabbit->hp = RABBIT_MAX_HP;
		//			}
		//
		//		}
		//	}
		//	//else {
		//	//	size_t atractorIndex = i;
		//	//	auto atractor = rabbit->GetActorLocation();
		//	//	float atractortDist = 1000;
		//	//	for (int j = 1; j < Rabbits.Num(); j++) {
		//	//		auto partner = Rabbits[j];
		//	//		auto vec = partner->GetActorLocation() - rabbit->GetActorLocation();
		//	//		float dist = vec.Size();
		//	//		if (dist < atractortDist && partner->hp > RABBIT_MAX_HUNGRY_HP_LEVEL && j != i) {
		//	//			atractorIndex = j;
		//	//			atractor = vec;
		//	//			atractortDist = dist;
		//	//		}
		//	//	}
		//	//	auto partner = Rabbits[atractorIndex];
		//	//	if (&rabbit != &partner) {
		//	//		rabbit->SetActorLocation(rabbit->GetActorLocation() + atractor / atractortDist * RABBIT_VELOCITY);
		//	//		if ((rabbit->GetActorLocation() - Rabbits[atractorIndex]->GetActorLocation()).Size() < SIZE) {
		//	//			rabbit->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		//	//			partner->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		//	//			/*for (int j = 0; j < RABBIT_REPRODUCE_COUNT; j++) {
		//	//				Rabbits.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), RABBIT_MAX_HUNGRY_HP_LEVEL));
		//	//			}*/
		//	//		}
		//	//	}
		//	//}
		//}


		// Wolfes

		if (Wolfes.Num() == 0)
		{
			for (int i = 0; i < WOLF_COUNT; i++) {
				//Wolfes.push_back(Wolf(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), WOLF_MAX_HUNGRY_HP_LEVEL));
			}
		}

		for (int i = 0; i < Wolfes.Num(); i++) {
			auto wolf = Wolfes[i];
			if (wolf->hp != 0) {
				wolf->hp--;
			}
			else {
				Wolfes.RemoveAt(i);
				i--;
				continue;
			}
		}

		for (int i = 0; i < Wolfes.Num(); i++) {
			auto wolf = Wolfes[i];

			if (wolf->hp <= WOLF_MAX_HUNGRY_HP_LEVEL) {
				if (Rabbits.Num() > 0) {
					size_t atractorIndex = 0;
					auto atractor = Rabbits[atractorIndex]->GetActorLocation() - wolf->GetActorLocation();
					float atractortDist = atractor.Size();
					for (int j = 1; j < Rabbits.Num(); j++) {
						auto rabbit = Rabbits[j];
						auto vec = rabbit->GetActorLocation() - wolf->GetActorLocation();
						float dist = vec.Size();
						if (dist < atractortDist) {
							atractorIndex = j;
							atractor = vec;
							atractortDist = dist;
						}
					}
					wolf->SetActorLocation(wolf->GetActorLocation() + atractor / atractortDist * WOLF_VELOCITY);

					if ((wolf->GetActorLocation() - Rabbits[atractorIndex]->GetActorLocation()).Size() < SIZE) {
						Rabbits.RemoveAt(atractorIndex);
						wolf->hp = WOLF_MAX_HP;
					}
				}
			}
			else {
				size_t atractorIndex = i;
				auto atractor = wolf->GetActorLocation();
				float atractortDist = 1000;
				for (int j = 1; j < Wolfes.Num(); j++) {
					auto& partner = Wolfes[j];
					auto vec = partner->GetActorLocation() - wolf->GetActorLocation();
					float dist = vec.Size();
					if (dist < atractortDist && partner->hp > WOLF_MAX_HUNGRY_HP_LEVEL && j != i) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				auto partner = Wolfes[atractorIndex];
				if (&wolf != &partner) {
					wolf->SetActorLocation(wolf->GetActorLocation() + atractor / atractortDist * WOLF_VELOCITY);
					if ((wolf->GetActorLocation() - Wolfes[atractorIndex]->GetActorLocation()).Size() < SIZE) {
						wolf->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
						partner->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
						for (int j = 0; j < WOLF_REPRODUCE_COUNT; j++) {
							//Wolfes.push_back(Wolf(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), WOLF_MAX_HUNGRY_HP_LEVEL));
						}
					}
				}
			}
		}
	}
	iter++;
}

template <typename ArrayClass, typename SubClass, class T>
void AAgentSpawner::SpawnActors(ArrayClass arrayClass, SubClass subClass, T clasa)
{
	/*TArray<UStaticMeshComponent*> Components;
	subClass.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);
	const FVector Origin = GetActorLocation();


	for (size_t i = 0; i < PLANT_COUNT; i++)
	{
		const FVector Loc(Origin.X + i * 15, Origin.Y, Origin.Z);
		APlantAgent* const SpawnedActorRef = GetWorld()->SpawnActor<APlantAgent>(subClass, Loc, GetActorRotation());
		Plants.Add(SpawnedActorRef);

	}*/
}