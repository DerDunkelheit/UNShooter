// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/ChainsExecutions/RotateTowardActor.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARotateTowardActor::ARotateTowardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Rotation Point"));
	SetRootComponent(RotationPoint);
	RotationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotation Mesh"));
	RotationMesh->SetupAttachment(RotationPoint);
}

// Called when the game starts or when spawned
void ARotateTowardActor::BeginPlay()
{
	Super::BeginPlay();

	ActorToRotate = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
}

// Called every frame
void ARotateTowardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bEnableMode) return;

	if(ActorToRotate != nullptr)
	{
		FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(RotationPoint->GetComponentLocation(), ActorToRotate->GetActorLocation());
		FRotator FinalRotator = UKismetMathLibrary::RInterpTo_Constant(RotationPoint->GetRelativeRotation(),LookRotator,DeltaTime,30);
		//FinalRotator.Pitch = RotationPoint->GetRelativeRotation().Pitch;
		//FinalRotator.Roll = RotationPoint->GetRelativeRotation().Roll;

		FinalRotator.Yaw = FMath::Clamp(FinalRotator.Yaw,(float)-70, (float)70);
		
		//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow,FString::Printf(TEXT("%f"), RotationPoint->GetRelativeRotation().Yaw));
		
		RotationPoint->SetWorldRotation(FinalRotator);
	}
}

