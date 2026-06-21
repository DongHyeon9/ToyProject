#include "Polygon.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Dot.h"
#include "Line.h"

void CPolygon::Render_Impl(HDC Buffer)
{
	std::array<POINT, 3> finalPoints{ points };
	POINT relativePoint = GetRelativePoint();
	for (auto& point : finalPoints)
		point -= relativePoint;

	::Polygon(Buffer, finalPoints.data(), static_cast<int32>(finalPoints.size()));
}

void CPolygon::SetArea(const RECT& Rect)
{
	points[0].x = static_cast<int32>((Rect.left + Rect.right) * 0.5f);
	points[0].y = Rect.top;
	points[1].x = Rect.right;
	points[1].y = Rect.bottom;
	points[2].x = Rect.left;
	points[2].y = Rect.bottom;
}

bool CPolygon::CheckOverlap(std::shared_ptr<const IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(Rhs), std::static_pointer_cast<const CPolygon>(shared_from_this()));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CPolygon>(shared_from_this()), std::static_pointer_cast<const CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CPolygon>(shared_from_this()), std::static_pointer_cast<const CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CPolygon>(shared_from_this()), std::static_pointer_cast<const CLine>(Rhs));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CPolygon>(shared_from_this()), std::static_pointer_cast<const CPolygon>(Rhs));

	default:	assert(false);	break;
	}

	return false;
}

bool CPolygon::CheckOverlap(const POINT& Point) const
{
	auto cp1 = EngineUtil::CrossProduct(points[0], points[1], Point);
	auto cp2 = EngineUtil::CrossProduct(points[1], points[2], Point);
	auto cp3 = EngineUtil::CrossProduct(points[2], points[0], Point);

	const bool bHasNegate{ cp1 < 0 || cp2 < 0 || cp3 < 0 };
	const bool bHasPositive{ cp1 > 0 || cp2 > 0 || cp3 > 0 };

	return !(bHasNegate && bHasPositive);
}

EState CPolygon::GetState() const
{
	return EState::Move;
}

void CPolygon::AddCoordinate(const POINT& Point)
{
	for (auto& point : points)
		point += Point;
}

void CPolygon::Resize(const POINT& Point)
{
	int32 xMin = points[0].x;
	int32 xMax = points[0].x;
	int32 yMin = points[0].y;
	int32 yMax = points[0].y;

	for (const auto& point : points)
	{
		xMin = min(xMin, point.x);
		xMax = max(xMax, point.x);
		yMin = min(yMin, point.y);
		yMax = max(yMax, point.y);
	}

	const POINT center{ (xMin + xMax) / 2, (yMin + yMax) / 2 };
	const int32 width = max(1, xMax - xMin);
	const int32 height = max(1, yMax - yMin);
	const int32 newWidth = max(2, width + Point.x * 2);
	const int32 newHeight = max(2, height + Point.y * 2);
	const double scaleX = static_cast<double>(newWidth) / width;
	const double scaleY = static_cast<double>(newHeight) / height;

	for (auto& point : points)
	{
		point.x = center.x + static_cast<int32>(std::round((point.x - center.x) * scaleX));
		point.y = center.y + static_cast<int32>(std::round((point.y - center.y) * scaleY));
	}
}

void CPolygon::ConfirmEdit()
{
	SetRelativePoint(POINT{});
}

void CPolygon::LogInfo() const
{
	const double area = std::abs(EngineUtil::CrossProduct(points[0], points[1], points[2])) * 0.5;
	LOG("Shape: Triangle, Points: (%d,%d), (%d,%d), (%d,%d), Area: %.2f",
		points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, area);
}
void CPolygon::SetPolygon(const std::array<POINT, 3>& Points)
{
	points = Points;
}

void CPolygon::SetPoint(const POINT& Point, int32 Idx)
{
	points[Idx] = Point;
}