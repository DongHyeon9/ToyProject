#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Dot.h"
#include "Line.h"

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

bool CCircle::CheckOverlap(std::shared_ptr<const IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };
	
	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(Rhs), std::static_pointer_cast<const CCircle>(shared_from_this()));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CCircle>(shared_from_this()), std::static_pointer_cast<const CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CDot>(Rhs), std::static_pointer_cast<const CCircle>(shared_from_this()));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CLine>(Rhs), std::static_pointer_cast<const CCircle>(shared_from_this()));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CPolygon>(Rhs), std::static_pointer_cast<const CCircle>(shared_from_this()));

	default:	assert(false);	break;
	}

	return false;
}

bool CCircle::CheckOverlap(const POINT& Point) const
{
	return radius >= std::sqrt(std::pow(Point.x - center.x, 2) + std::pow(Point.y - center.y, 2));
}

EState CCircle::GetState() const
{
	return EState::Move;
}

void CCircle::AddCoordinate(const POINT& Point)
{
	center += Point;
}

void CCircle::Resize(const POINT& Point)
{
	radius = max(1, radius + Point.x + Point.y);
}
void CCircle::ConfirmEdit()
{
	center += GetRelativePoint();
	SetRelativePoint(POINT{});
}

void CCircle::LogInfo() const
{
	double area = 3.14 * radius * radius;
	LOG("원, 중심 (%d,%d), 반지름 %d, 넓이: %.2f", center.x, center.y, radius, area);
}
void CCircle::SetCenter(const POINT& Point)
{
	center = Point;
}

void CCircle::SetRadius(int32 Radius)
{
	radius = Radius;
}
