#include "Circle.h"

void CCircle::Render_Impl(HDC Buffer)
{
	POINT finalCenter{ center - GetRelativePoint() };
	::Ellipse(Buffer
		, finalCenter.x - radius
		, finalCenter.y - radius
		, finalCenter.x + radius
		, finalCenter.y + radius);
}

void CCircle::SetArea(const RECT& Rect)
{
	center.x = static_cast<int32>((Rect.left + Rect.right) * 0.5f);
	center.y = static_cast<int32>((Rect.top + Rect.bottom) * 0.5f);
	
	radius = min(std::abs(Rect.left - Rect.right), std::abs(Rect.top - Rect.bottom));
}

bool CCircle::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	return true;
}

EState CCircle::GetState() const
{
	return EState();
}

void CCircle::EditShape(const RECT& Rect)
{
}

void CCircle::ConfirmEdit()
{
}

void CCircle::AddCoordinate(const POINT& Point)
{
	center += Point;
}

void CCircle::SetCenter(const POINT& Point)
{
	center = Point;
}

void CCircle::SetRadius(int32 Radius)
{
	radius = Radius;
}
