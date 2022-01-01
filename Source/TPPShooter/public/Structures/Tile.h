#pragma once

#include "CoreMinimal.h"
#include "Templates/TypeHash.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	FTile() = default;

	FTile(int x, int y);

	//Supporting hash types, so we can use it inside TMap
	//bool operator==(const FTile& Other) const;
	//uint32 GetTypeHash(const FTile& InPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int X = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Y = 0;
};
