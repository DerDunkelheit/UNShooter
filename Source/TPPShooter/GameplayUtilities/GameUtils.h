#pragma once

namespace GameUtils
{
	//TODO: replace to cpp file?????
	bool TryHitFromEye(AActor* caster, float lineTraceRange, AActor*& hitActorOut)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		caster->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * lineTraceRange);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(caster);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (caster->GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			hitActorOut = Hit.GetActor();
			return true;
		}

		return false;
	}

	bool TryHitFromEye(AActor* caster, float lineTraceRange, AActor*& hitActorOut, FVector& traceStartOut, FVector& traceEndOut)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		caster->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * lineTraceRange);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(caster);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (caster->GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			hitActorOut = Hit.GetActor();
			traceStartOut = EyeLocation;
			traceEndOut = TraceEnd;
			return true;
		}

		return false;
	}
} // namespace gameUtils