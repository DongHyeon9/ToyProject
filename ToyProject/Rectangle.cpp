#include "Rectangle.h"

void CRectangle::Render_Impl(HDC Buffer)
{
	const POINT relativePoint = GetRelativePoint();
	POINT finalLT = lt - relativePoint;
	POINT finalRB = rb - relativePoint;
	::Rectangle(Buffer, finalLT.x, finalLT.y, finalRB.x, finalRB.y);
}

void CRectangle::SetArea(const RECT& Rect)
{
	SetRenctangle(Rect);
}

bool CRectangle::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	return true;
}

EState CRectangle::GetState() const
{
	return EState();
}

void CRectangle::EditShape(const RECT& Rect)
{
}

void CRectangle::ConfirmEdit()
{
}

void CRectangle::AddCoordinate(const POINT& Point)
{
	lt += Point;
	rb += Point;
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
