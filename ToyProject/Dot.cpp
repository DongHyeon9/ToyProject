#include "Dot.h"

void CDot::Render_Impl(HDC Buffer)
{
	::Ellipse(Buffer
		, point.x - SIZE
		, point.y - SIZE
		, point.x + SIZE
		, point.y + SIZE);
}

void CDot::SelectedRender_Impl(HDC Buffer)
{

}

bool CDot::CheckCollision(const POINT& pt) const
{
	return false;
}

void CDot::SetArea(const RECT& Rect)
{
	point.x = Rect.right;
	point.y = Rect.bottom;
}

void CDot::SetPoint(const POINT& Point)
{
	point = Point;
}
