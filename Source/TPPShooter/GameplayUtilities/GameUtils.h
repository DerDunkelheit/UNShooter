#pragma once
#include "Animation/WidgetAnimation.h"

namespace GameUtils
{
	bool TryHitFromEye(AActor* caster, float lineTraceRange, AActor*& hitActorOut);
	bool TryHitFromEye(AActor* caster, float lineTraceRange, AActor*& hitActorOut, FVector& traceStartOut, FVector& traceEndOut);

	void StoreWidgetAnimations(UObject* widget, TMap<FName, UWidgetAnimation*>& animationsMapOut);
	
} // namespace gameUtils