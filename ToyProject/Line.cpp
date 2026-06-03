#include "Line.h"

static constexpr int32 TEMP_OFFSET{ 5 };

void CLine::Render_Impl(HDC Buffer)
{
	POINT relativePoint{ GetRelativePoint() };
	POINT finalStart{ start - relativePoint };
	POINT finalEnd{ end - relativePoint };
	::MoveToEx(Buffer, finalStart.x, finalStart.y, nullptr);
	::LineTo(Buffer, finalEnd.x, finalEnd.y);
}

void CLine::SetArea(const RECT& Rect)
{
	start.x = Rect.left;
	start.y = Rect.top;
	end.x = Rect.right;
	end.y = Rect.bottom;
}

bool CLine::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	return true;
}

EState CLine::GetState() const
{
	return EState();
}

void CLine::EditShape(const RECT& Rect)
{
}

void CLine::ConfirmEdit()
{
}

void CLine::AddCoordinate(const POINT& Point)
{
	start += Point;
	end += Point;
}

void CLine::SetStart(const POINT& Point)
{
	start = Point;
}

void CLine::SetEnd(const POINT& Point)
{
	end = Point;
}
