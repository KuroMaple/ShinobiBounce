#pragma once

#include "CoreMinimal.h"
#include "PongTypes.generated.h" 

UENUM(BlueprintType)
enum class EGoalSide : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
};
