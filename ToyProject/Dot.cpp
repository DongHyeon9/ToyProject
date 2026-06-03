#include "Dot.h"

void CDot::Render_Impl(HDC Buffer)
{
	POINT finalPoint{ point - GetRelativePoint() };
	::Ellipse(Buffer
		, finalPoint.x - SIZE
		, finalPoint.y - SIZE
		, finalPoint.x + SIZE
		, finalPoint.y + SIZE);
}

void CDot::SetArea(const RECT& Rect)
{
	point.x = Rect.right;
	point.y = Rect.bottom;
}

bool CDot::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	return true;
}

EState CDot::GetState() const
{
	return EState();
}

void CDot::EditShape(const RECT& Rect)
{
}

void CDot::ConfirmEdit()
{
}

void CDot::AddCoordinate(const POINT& Point)
{
	point += Point;
}

void CDot::SetPoint(const POINT& Point)
{
	point = Point;
}
