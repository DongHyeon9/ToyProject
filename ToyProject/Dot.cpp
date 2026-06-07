#include "Dot.h"

void CDot::Render_Impl(HDC Buffer)
{
	POINT finalPoint{ point - GetRelativePoint() };
	::Ellipse(Buffer
		, finalPoint.x - SIZE
		, finalPoint.y - SIZE
		, finalPoint.x + SIZE
		, finalPoint.y + SIZE);
}

void CDot::SetArea(const RECT& Rect)
{
	point.x = Rect.right;
	point.y = Rect.bottom;
}

bool CDot::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(Rhs), std::static_pointer_cast<CDot>(shared_from_this()));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<CDot>(shared_from_this()), std::static_pointer_cast<CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<CDot>(shared_from_this()), std::static_pointer_cast<CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<CLine>(Rhs), std::static_pointer_cast<CDot>(shared_from_this()));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<CPolygon>(Rhs), std::static_pointer_cast<CDot>(shared_from_this()));

	default:	assert(false);	break;
	}

	return false;
}

bool CDot::CheckOverlap(const POINT& Point) const
{
	return false;
}

EState CDot::GetState() const
{
	return EState::Move;
}

void CDot::AddCoordinate(const POINT& Point)
{
	point += Point;
}

void CDot::CandidateEditPoint(std::shared_ptr<IShape> Rect)
{
}

void CDot::ConfirmEdit()
{
	point += GetRelativePoint();
	SetRelativePoint(POINT{});
}

void CDot::SetPoint(const POINT& Point)
{
	point = Point;
}
