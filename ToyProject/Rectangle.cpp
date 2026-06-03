#include "Rectangle.h"

void CRectangle::Render_Impl(HDC Buffer)
{
	::Rectangle(Buffer, lt.x, lt.y, rb.x, rb.y);
}

void CRectangle::SelectedRender_Impl(HDC Buffer)
{
	
}

bool CRectangle::CheckCollision(const POINT& pt) const
{
	return false;
}

void CRectangle::SetArea(const RECT& Rect)
{
	SetRenctangle(Rect);
}

void CRectangle::SetRenctangle(const POINT& LT, const POINT& RB)
{
	lt = LT;
	rb = RB;
}

void CRectangle::SetRenctangle(const RECT& Rect)
{
	lt.x = Rect.left;
	lt.y = Rect.top;
	rb.x = Rect.right;
	rb.y = Rect.bottom;
}

void CRectangle::SetLeftTop(const POINT& LT)
{
	lt = LT;
}

void CRectangle::SetRightBottom(const POINT& RB)
{
	rb = RB;
}

void CRectangle::SetLeft(int32 Value)
{
	lt.x = Value;
}

void CRectangle::SetTop(int32 Value)
{
	lt.y = Value;
}

void CRectangle::SetRight(int32 Value)
{
	rb.x = Value;
}

void CRectangle::SetBottom(int32 Value)
{
	rb.y = Value;
}
