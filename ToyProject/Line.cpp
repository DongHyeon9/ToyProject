#include "Line.h"

static constexpr int32 TEMP_OFFSET{ 5 };

void CLine::Render_Impl(HDC Buffer)
{
	::MoveToEx(Buffer, start.x, start.y, nullptr);
	::LineTo(Buffer, end.x, end.y);
}

void CLine::SelectedRender_Impl(HDC Buffer)
{
}

bool CLine::CheckCollision(const POINT& pt) const
{
	return false;
}

void CLine::SetArea(const RECT& Rect)
{
	start.x = Rect.left;
	start.y = Rect.top;
	end.x = Rect.right;
	end.y = Rect.bottom;
}

void CLine::SetStart(const POINT& Point)
{
	start = Point;
}

void CLine::SetEnd(const POINT& Point)
{
	end = Point;
}
