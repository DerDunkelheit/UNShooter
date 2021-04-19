// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TPPShooter/TPPShooterCharacter.h"

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(
	TEXT("Game.DebugWeapons"),
	DebugWeaponDrawing,
	TEXT("Draw Debug Lines for Weapons"),
	ECVF_Cheat);

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	MuzzleSocketName = "MuzzleSocket";

	RateOfFire = 600;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	Subscribe();

	TimerBetweenShot = 60/ RateOfFire;
	LastFireTime = -1;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::StartFire()
{
	//TODO: create fire modes, for that we can use common interface in which we'll write shooting logic
	float FirstDelay = FMath::Max( LastFireTime + TimerBetweenShot - GetWorld()->TimeSeconds, 0.0f);
	
    GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots,this,&AWeapon::Fire,TimerBetweenShot,true,FirstDelay);
}

void AWeapon::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void AWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, Hit, MyOwner->GetInstigatorController(),
			                                   this, DamageType);

			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint,
				                                         Hit.ImpactNormal.Rotation());
			}
		}

		OnFire();

		if (DebugWeaponDrawing > 0)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1, 0, 1);
		}

		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void AWeapon::OnPlayerDied_Implementation()
{
}

void AWeapon::Subscribe()
{
	auto Player = Cast<ATPPShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->HealthComponent->OnHealthDepleted.AddDynamic(this, &AWeapon::OnPlayerDied);
	}
}
