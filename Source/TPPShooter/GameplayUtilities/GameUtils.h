#pragma once
#include "Animation/WidgetAnimation.h"

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

	void StoreWidgetAnimations(UObject* widget, TMap<FName, UWidgetAnimation*>& animationsMapOut)
	{
		animationsMapOut.Empty();

		FProperty* prop = widget->GetClass()->PropertyLink;
 
		// Run through all properties of this class to find any widget animations
		while( prop != nullptr  )
		{
			// Only interested in object properties
			if( prop->GetClass() == FObjectProperty::StaticClass() )
			{
				FObjectProperty* objectProp = CastField<FObjectProperty>(prop);
 
				// get only  properties that are widget animations
				if( objectProp->PropertyClass == UWidgetAnimation::StaticClass() )
				{
					UObject* object = objectProp->GetObjectPropertyValue_InContainer( widget );
					UWidgetAnimation* widgetAnim = Cast<UWidgetAnimation>(object);
 
					if( widgetAnim != nullptr && widgetAnim->MovieScene)
					{
						FName animName = widgetAnim->MovieScene->GetFName();
						animationsMapOut.Add(animName, widgetAnim);
					}
				}
			}
 
			prop = prop->PropertyLinkNext;
		}
	}
} // namespace gameUtils