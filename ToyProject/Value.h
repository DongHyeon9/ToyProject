#pragma once
#include "Enum.h"

inline const FString WINDOW_CLASS{ TEXT("ToyProjectClass") };
inline const FString WINDOW_TITLE{ TEXT("ToyProject") };

constexpr double EPSILON{ 0.000001 };

namespace ZOrder
{
	constexpr int32 NONE{ 0 };
	constexpr int32 SELECT{ 0 };
}