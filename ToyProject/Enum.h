#pragma once
#include "Type.h"

enum class EState : uint8
{
	None,

	Selected,
	Create,
};

enum class EShapeType : uint8
{
	None,

	Dot,
	Line,
	Circle,
	Triangle,
	Rect
};

enum class EPenType : uint8
{ 
	Black,
	Red,
	Green,
	Blue,

	SelectBox,
	Selected,
};

enum class EBrushType : uint8
{
	White,
	Red,
	Green,
	Blue,
	Black,

	SelectBox,
	Selected,
};