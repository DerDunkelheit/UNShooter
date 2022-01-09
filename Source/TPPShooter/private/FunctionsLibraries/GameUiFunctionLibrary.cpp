// Fill out your copyright notice in the Description page of Project Settings.

#include "FunctionsLibraries/GameUiFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UGameUiFunctionLibrary::MousePositionInTile(float TileSize, float X, float Y,
                                                    bool& RightSideOut, bool& DownSideOut)
{
	RightSideOut = UKismetMathLibrary::GenericPercent_FloatFloat(X, TileSize) > TileSize / 2;
	DownSideOut = UKismetMathLibrary::GenericPercent_FloatFloat(Y, TileSize) > TileSize / 2;
}
