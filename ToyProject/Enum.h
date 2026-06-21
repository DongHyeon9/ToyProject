#pragma once
#include "Type.h"

enum class EState : uint8
{
	Idle,

	Selecting,
	Move,
	Edit,
	Create,
};

enum class EShapeType : uint8
{
	None,

	Dot,
	Line,
	Circle,
	Polygon,
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
	Edit,
	TempShape,
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
	Edit,
	TempShape,
};
