#include "Circle.h"

void CCircle::Render_Impl(HDC Buffer)
{
	::Ellipse(Buffer
		, center.x - radius
		, center.y - radius
		, center.x + radius
		, center.y + radius);
}

void CCircle::SelectedRender_Impl(HDC Buffer)
{
}

bool CCircle::CheckCollision(const POINT& pt) const
{
	return false;
}

void CCircle::SetArea(const RECT& Rect)
{
	center.x = static_cast<int32>((Rect.left + Rect.right) * 0.5f);
	center.y = static_cast<int32>((Rect.top + Rect.bottom) * 0.5f);
	
	radius = min(std::abs(Rect.left - Rect.right), std::abs(Rect.top - Rect.bottom));
}

void CCircle::SetCenter(const POINT& Point)
{
	center = Point;
}

void CCircle::SetRadius(int32 Radius)
{
	radius = Radius;
}
