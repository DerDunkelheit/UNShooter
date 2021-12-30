#pragma once

#include "CoreMinimal.h"

#include "GameUtilsFunctionLibrary.generated.h"

UCLASS()
class TPPSHOOTER_API UGameUtilsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// WorldContext meta implicitly sets worldContextObject to self, so we can omit manually assigning self reference.
	// DeterminesOutputType meta implicitly casts return type to current subclass in the BP. So we get casted AActor as an output pin.
	UFUNCTION(BlueprintCallable, Category="GameUtilities",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass"))
	static AActor* GetNearestActorOfClass(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FVector Location, float Radius = 512.f);
};
