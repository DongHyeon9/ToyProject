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
}