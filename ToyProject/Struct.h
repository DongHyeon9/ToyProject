#pragma once
#include "Value.h"

template<class T>
class ISingleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

protected:
	ISingleton() = default;
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
};

struct Material
{
	EPenType penType{};
	EBrushType brushType{};
};

struct Vector2
{
	float x{};
	float y{};
};

struct WindowDesc
{
	HINSTANCE instance{};
	HWND wnd{};
	int32 cmdShow{};
	Vector2 size{ 1280, 720 };
};
