#pragma once

#include "CoreMinimal.h"
#include "Line.generated.h"

//Class for holding positions for drawing grid's segments.
USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D End;

	FLine() = default;

	FLine(FVector2D start, FVector2D end);
};
