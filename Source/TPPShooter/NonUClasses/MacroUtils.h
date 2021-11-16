#pragma once

#define NAMEOF(name) #name
#define SCREEN_LOG(key, text) if (GEngine) GEngine->AddOnScreenDebugMessage(key,2,FColor::Orange, TEXT(text));
#define SCREEN_LOG_STRING(key, text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(key, 2, FColor::Orange, FString::Printf(TEXT(text), fstring))