#pragma once
#include "Struct.h"

namespace EngineUtil
{
	template<class T>
	FString ToString(const T& Value)
	{
#ifdef UNICODE
		return std::to_wstring(Value);
#else
		return std::to_string(Value);
#endif
	}

	template<class T>
	T RandomRange(T Min, T Max)
	{
		std::random_device rd{};
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min(static_cast<int>(Min), static_cast<int>(Max)), max(static_cast<int>(Min), static_cast<int>(Max)));
		return static_cast<T>(dis(gen));
	}
}


inline POINT operator+(const POINT& Lhs, const POINT& Rhs)
{
	return POINT{ Lhs.x + Rhs.x, Lhs.y + Rhs.y };
}


inline POINT operator-(const POINT& Lhs, const POINT& Rhs)
{
	return POINT{ Lhs.x - Rhs.x, Lhs.y - Rhs.y };
}

inline void operator+=(POINT& Lhs, const POINT& Rhs)
{
	Lhs.x += Rhs.x;
	Lhs.y += Rhs.y;
}

inline void operator-=(POINT& Lhs, const POINT& Rhs)
{
	Lhs.x -= Rhs.x;
	Lhs.y -= Rhs.y;
}