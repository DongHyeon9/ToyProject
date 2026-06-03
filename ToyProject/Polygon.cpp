#include "Polygon.h"

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

bool CPolygon::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	return true;
}

EState CPolygon::GetState() const
{
	return EState();
}

void CPolygon::EditShape(const RECT& Rect)
{
}

void CPolygon::ConfirmEdit()
{
}

void CPolygon::AddCoordinate(const POINT& Point)
{
	for (auto& point : points)
		point += Point;
}

void CPolygon::SetPolygon(const std::array<POINT, 3>& Points)
{
	points = Points;
}

void CPolygon::SetPoint(const POINT& Point, int32 Idx)
{
	points[Idx] = Point;
}
