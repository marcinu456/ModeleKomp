// Fill out your copyright notice in the Description page of Project Settings.


#include "RabbitAgent.h"

#include "PlantAgent.h"
#include "Kismet/GameplayStatics.h"

ARabbitAgent::ARabbitAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ARabbitAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void ARabbitAgent::Move()
{
	Super::Move();

	TArray<AActor*> Plants;

	//TSubclassOf<APlantAgent> PlantActor;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlantActor, AllActors);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlantAgent::StaticClass(), Plants);

	//auto Plant = Cast<TArray<APlantAgent*>>(AllActors.GetData());

	//TArray<APlantAgent*> Plants = AgentSpawner->GetPlants();
	if (hp <= RABBIT_MAX_HUNGRY_HP_LEVEL) {
			if (Plants.Num() > 0) {
				size_t atractorIndex = 0;
				auto atractor = Cast<APlantAgent>(Plants[atractorIndex])->GetActorLocation() - GetActorLocation();
				float atractortDist = atractor.Size();// Plants[atractorIndex]->GetActorLocation(), rabbit->GetActorLocation());
				for (int j = 1; j < Plants.Num(); j++) {
					auto* plant = Cast<APlantAgent>(Plants[j]);
					FVector vec = plant->GetActorLocation() - GetActorLocation();
					float dist = vec.Size();// FVector::Distance(plant->GetActorLocation(), rabbit->GetActorLocation());
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				UE_LOG(LogTemp, Warning, TEXT("atractor X=%f , Y=%f / atractortDist %f "), atractor.X, atractor.Y, atractortDist);
				SetActorLocation(GetActorLocation() + atractor / atractortDist * RABBIT_VELOCITY);
				UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
	
				if ((GetActorLocation() - Plants[atractorIndex]->GetActorLocation()).Size() < SIZE) {
					Plants.RemoveAt(atractorIndex);
					hp = RABBIT_MAX_HP;
				}
	
			}
		}
	//else {
	//	size_t atractorIndex = i;
	//	auto atractor = GetActorLocation();
	//	float atractortDist = 1000;
	//	for (int j = 1; j < Rabbits.Num(); j++) {
	//		auto partner = Rabbits[j];
	//		auto vec = partner->GetActorLocation() - GetActorLocation();
	//		float dist = vec.Size();
	//		if (dist < atractortDist && partner->hp > RABBIT_MAX_HUNGRY_HP_LEVEL && j != i) {
	//			atractorIndex = j;
	//			atractor = vec;
	//			atractortDist = dist;
	//		}
	//	}
	//	auto partner = Rabbits[atractorIndex];
	//	if (this != &partner) {
	//		SetActorLocation(GetActorLocation() + atractor / atractortDist * RABBIT_VELOCITY);
	//		if ((GetActorLocation() - Rabbits[atractorIndex]->GetActorLocation()).Size() < SIZE) {
	//			hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
	//			partner->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
	//			/*for (int j = 0; j < RABBIT_REPRODUCE_COUNT; j++) {
	//				Rabbits.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), RABBIT_MAX_HUNGRY_HP_LEVEL));
	//			}*/
	//		}
	//	}
	//}
}
