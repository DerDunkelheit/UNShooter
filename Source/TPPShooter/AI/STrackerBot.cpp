// Fill out your copyright notice in the Description page of Project Settings.


#include "STrackerBot.h"


#include "DrawDebugHelpers.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ASTrackerBot::ASTrackerBot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ExplosionRadius = 300;
	ExplosionRadiusOffset = 100;
	ExplosionDamage = 200;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCanEverAffectNavigation(false);
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;
	PlayerDetectArea = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectArea"));
	PlayerDetectArea->SetSphereRadius(ExplosionRadius);
	PlayerDetectArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlayerDetectArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerDetectArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PlayerDetectArea->SetupAttachment(RootComponent);
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadioForceComponent"));
	RadialForceComponent->Radius = ExplosionRadius + ExplosionRadiusOffset;
	RadialForceComponent->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	MovementForce = 1000;
	bUseVelocityChange = false;
	RequiredDistanceToTarget = 100;
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();

    HealthComponent->OnHealthDepleted.AddDynamic(this, &ASTrackerBot::DieEvent);
	
	NextPathPoint = GetNextPathPoint();
}

// Called every frame
void ASTrackerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	if (DistanceToTarget <= RequiredDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();

		DrawDebugString(GetWorld(), GetActorLocation(), "Target Reached!");
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= MovementForce;

		MeshComponent->AddForce(ForceDirection, NAME_None, bUseVelocityChange);

		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + ForceDirection, 32,
		                          FColor::Orange, false, 0, 0, 1);
	}

	DrawDebugSphere(GetWorld(), NextPathPoint, 20,12,FColor::Orange, false, 0,1);
}

FVector ASTrackerBot::GetNextPathPoint()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UNavigationPath* NavPath =
		UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), Player);
	if (NavPath->PathPoints.Num() > 1)
	{
		return NavPath->PathPoints[1];
	}

	return GetActorLocation();
}
