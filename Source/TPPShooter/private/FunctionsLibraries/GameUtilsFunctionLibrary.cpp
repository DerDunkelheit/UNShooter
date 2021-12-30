#include "FunctionsLibraries/GameUtilsFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"

AActor* UGameUtilsFunctionLibrary::GetNearestActorOfClass(const UObject* WorldContextObject,
                                                          TSubclassOf<AActor> ActorClass, FVector Location, float Radius)
{
	AActor* nearestActor = nullptr;
	float nearestDistance = Radius;

	TArray<AActor*> actorsOut;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ActorClass, actorsOut);

	for(AActor* currentActor : actorsOut)
	{
		float distance = FVector::Distance(Location, currentActor->GetActorLocation());

		if(distance < nearestDistance)
		{
			nearestActor = currentActor;
			nearestDistance = distance;
		}
	}
	
	return nearestActor;
}
