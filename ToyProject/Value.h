#pragma once
#include "Enum.h"

inline const FString WINDOW_CLASS{ TEXT("ToyProjectClass") };
inline const FString WINDOW_TITLE{ TEXT("ToyProject") };
inline constexpr double PICK_TOLERANCE{ 6.0 };

constexpr double EPSILON{ 0.000001 };

namespace ZOrder
{
	constexpr int32 NONE{ 0 };
	constexpr int32 SELECT{ 0 };
}