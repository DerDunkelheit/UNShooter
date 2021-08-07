// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/ObserverActor.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AObserverActor::AObserverActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	SetRootComponent(ActorMesh);
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	SpotLight->SetupAttachment(ActorMesh);
}

// Called when the game starts or when spawned
void AObserverActor::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SpotLight->SetOuterConeAngle(ObserverAngle / 2);
}

// Called every frame
void AObserverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), ObserverRadius, 32, FColor::Orange);

	if (bInstantSpot)
	{
		CanSeePlayer() ? PlayerVisibleTimer += DeltaTime : PlayerVisibleTimer -= DeltaTime;
		PlayerVisibleTimer = FMath::Clamp<float>(PlayerVisibleTimer, 0, TimerToSpotPlayer);
		SpotLight->SetLightColor(FLinearColor::LerpUsingHSV(FColor::White, FColor::Red, PlayerVisibleTimer / TimerToSpotPlayer));
	}
	else
	{
		SpotLight->SetLightColor(CanSeePlayer() ? FColor::Red : FColor::White);
	}
}

bool AObserverActor::CanSeePlayer()
{
	verifyf(Player != nullptr, TEXT("Player wasn't found"))

	FVector PlayerPosition = Player->GetActorLocation();
	FVector DirToPlayer = PlayerPosition - GetActorLocation();
	DirToPlayer.Normalize();

	float DistanceBetween = (PlayerPosition - GetActorLocation()).Size();
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,FString::Printf(TEXT("Distance to Player: %f"), DistanceBetween));

	if (DistanceBetween < ObserverRadius)
	{
		float AngleBetween = FMath::RadiansToDegrees(
			FMath::Acos(FVector::DotProduct(GetActorForwardVector(), DirToPlayer)));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, FString::Printf(TEXT("%f"), AngleBetween));

		return AngleBetween < ObserverAngle / 2 ? true : false;
	}

	return false;
}

void AObserverActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SpotLight->SetOuterConeAngle(ObserverAngle / 2);
}