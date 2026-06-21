#include "Line.h"
#include "GDIManager.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Dot.h"

void CLine::Render_Impl(HDC Buffer)
{
	POINT relativePoint{ GetRelativePoint() };
	POINT finalStart{ points[0] - relativePoint };
	POINT finalEnd{ points[1] - relativePoint };
	::MoveToEx(Buffer, finalStart.x, finalStart.y, nullptr);
	::LineTo(Buffer, finalEnd.x, finalEnd.y);
}

void CLine::SetArea(const RECT& Rect)
{
	points[0].x = Rect.left;
	points[0].y = Rect.top;
	points[1].x = Rect.right;
	points[1].y = Rect.bottom;
}

bool CLine::CheckOverlap(std::shared_ptr<const IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(Rhs), std::static_pointer_cast<const CLine>(shared_from_this()));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CLine>(shared_from_this()), std::static_pointer_cast<const CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CLine>(shared_from_this()), std::static_pointer_cast<const CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CLine>(shared_from_this()), std::static_pointer_cast<const CLine>(Rhs));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CPolygon>(Rhs), std::static_pointer_cast<const CLine>(shared_from_this()));

	default:	assert(false);	break;
	}

	return false;
}

bool CLine::CheckOverlap(const POINT& Point) const
{
	const double dx = static_cast<double>(points[1].x - points[0].x);
	const double dy = static_cast<double>(points[1].y - points[0].y);
	const double lengthSquared = dx * dx + dy * dy;

	if (lengthSquared <= EPSILON)
	{
		const double px = static_cast<double>(Point.x - points[0].x);
		const double py = static_cast<double>(Point.y - points[0].y);
		return std::sqrt(px * px + py * py) <= PICK_TOLERANCE;
	}

	const double t = std::clamp(((Point.x - points[0].x) * dx + (Point.y - points[0].y) * dy) / lengthSquared, 0.0, 1.0);
	const double closestX = points[0].x + t * dx;
	const double closestY = points[0].y + t * dy;
	const double distanceX = Point.x - closestX;
	const double distanceY = Point.y - closestY;

	return std::sqrt(distanceX * distanceX + distanceY * distanceY) <= PICK_TOLERANCE;
}

EState CLine::GetState() const
{
	return EState::Move;
}

void CLine::AddCoordinate(const POINT& Point)
{
	points[0] += Point;
	points[1] += Point;
}

void CLine::Resize(const POINT& Point)
{
	POINT center{ (points[0].x + points[1].x) / 2, (points[0].y + points[1].y) / 2 };
	POINT vector{ points[1].x - center.x, points[1].y - center.y };

	vector.x += vector.x >= 0 ? Point.x : -Point.x;
	vector.y += vector.y >= 0 ? Point.y : -Point.y;

	if (std::abs(vector.x) < 1)
		vector.x = vector.x < 0 ? -1 : 1;
	if (std::abs(vector.y) < 1)
		vector.y = vector.y < 0 ? -1 : 1;

	points[0] = center - vector;
	points[1] = center + vector;
}

void CLine::ConfirmEdit()
{
	SetRelativePoint(POINT{});
}

void CLine::LogInfo() const
{
	const double dx = static_cast<double>(points[1].x - points[0].x);
	const double dy = static_cast<double>(points[1].y - points[0].y);
	const double length = std::sqrt(dx * dx + dy * dy);
	LOG("Shape: Line, Start: (%d,%d), End: (%d,%d), Length: %.2f", points[0].x, points[0].y, points[1].x, points[1].y, length);
}
void CLine::SetStart(const POINT& Point)
{
	points[0] = Point;
}

void CLine::SetEnd(const POINT& Point)
{
	points[1] = Point;
}