#include "Rectangle.h"
#include "Polygon.h"
#include "Circle.h"
#include "Dot.h"
#include "Line.h"

void CRectangle::Render_Impl(HDC Buffer)
{
	std::array<POINT, 4> finalPoints{ points };
	const POINT relativePoint = GetRelativePoint();
	for (auto& point : finalPoints)
		point -= relativePoint;

	::Polygon(Buffer, finalPoints.data(), static_cast<int32>(finalPoints.size()));
}

void CRectangle::SetArea(const RECT& Rect)
{
	SetRenctangle(Rect);
}

bool CRectangle::CheckOverlap(std::shared_ptr<const IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(shared_from_this()), std::static_pointer_cast<const CRectangle>(Rhs));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(shared_from_this()), std::static_pointer_cast<const CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(shared_from_this()), std::static_pointer_cast<const CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(shared_from_this()), std::static_pointer_cast<const CLine>(Rhs));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<const CRectangle>(shared_from_this()), std::static_pointer_cast<const CPolygon>(Rhs));

	default:	assert(false);	break;
	}

	return false;
}

bool CRectangle::CheckOverlap(const POINT& Point) const
{
	int32 xMax{ points[0].x };
	int32 xMin{ points[0].x };
	int32 yMax{ points[0].y };
	int32 yMin{ points[0].y };

	for (const auto& point : points)
	{
		xMax = max(xMax, point.x);
		xMin = min(xMin, point.x);
		yMax = max(yMax, point.y);
		yMin = min(yMin, point.y);
	}

	return Point.x >= xMin && Point.y >= yMin && Point.x <= xMax && Point.y <= yMax;
}

EState CRectangle::GetState() const
{
	return EState::Move;
}

void CRectangle::AddCoordinate(const POINT& Point)
{
	for (auto& point : points)
		point += Point;
}

void CRectangle::Resize(const POINT& Point)
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
	const int32 newHalfWidth = max(1, (xMax - xMin) / 2 + Point.x);
	const int32 newHalfHeight = max(1, (yMax - yMin) / 2 + Point.y);

	SetRenctangle({ center.x - newHalfWidth, center.y - newHalfHeight }, { center.x + newHalfWidth, center.y + newHalfHeight });
}

void CRectangle::ConfirmEdit()
{
	SetRelativePoint(POINT{});
}

void CRectangle::LogInfo() const
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

	const int32 width = xMax - xMin;
	const int32 height = yMax - yMin;
	LOG("Shape: Rectangle, Points: (%d,%d), (%d,%d), (%d,%d), (%d,%d), Width: %d, Height: %d, Area: %d",
		points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, points[3].x, points[3].y, width, height, width * height);
}
void CRectangle::SetRenctangle(const POINT& LT, const POINT& RB)
{
	points[0].x = LT.x;
	points[0].y = LT.y;
	points[1].x = RB.x;
	points[1].y = LT.y;
	points[2].x = RB.x;
	points[2].y = RB.y;
	points[3].x = LT.x;
	points[3].y = RB.y;
}

void CRectangle::SetRenctangle(const RECT& Rect)
{
	SetRenctangle({ Rect.left,Rect.top }, { Rect.right,Rect.bottom });
}