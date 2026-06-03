#include "Polygon.h"

void CPolygon::Render_Impl(HDC Buffer)
{
	::Polygon(Buffer, points.data(), static_cast<int32>(points.size()));
}

void CPolygon::SelectedRender_Impl(HDC Buffer)
{
}

bool CPolygon::CheckCollision(const POINT& pt) const
{
	return false;
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

void CPolygon::SetPolygon(const std::array<POINT, 3>& Points)
{
	points = Points;
}

void CPolygon::SetPoint(const POINT& Point, int32 Idx)
{
	points[Idx] = Point;
}
