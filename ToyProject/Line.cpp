#include "Line.h"

static constexpr int32 TEMP_OFFSET{ 5 };

void CLine::Render_Impl(HDC Buffer)
{
	POINT relativePoint{ GetRelativePoint() };
	POINT finalStart{ points[0] - relativePoint};
	POINT finalEnd{ points[1] - relativePoint};
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

bool CLine::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(Rhs), std::static_pointer_cast<CLine>(shared_from_this()));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<CLine>(shared_from_this()), std::static_pointer_cast<CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<CLine>(shared_from_this()), std::static_pointer_cast<CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<CLine>(shared_from_this()), std::static_pointer_cast<CLine>(Rhs));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<CPolygon>(Rhs), std::static_pointer_cast<CLine>(shared_from_this()));

	default:	assert(false);	break;
	}

	return false;
}

bool CLine::CheckOverlap(const POINT& Point) const
{
	return false;
}

EState CLine::GetState() const
{
	return editPointIdx.empty() ? EState::Move : EState::Edit;
}

void CLine::AddCoordinate(const POINT& Point)
{
	points[0] += Point;
	points[1] += Point;
}

void CLine::CandidateEditPoint(std::shared_ptr<IShape> Rect)
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (Rect->CheckOverlap(points[i]))
			editPointIdx.emplace_back(i);
	}
}

void CLine::ConfirmEdit()
{
	SetRelativePoint(POINT{});
	editPointIdx.clear();
}

void CLine::SetStart(const POINT& Point)
{
	points[0] = Point;
}

void CLine::SetEnd(const POINT& Point)
{
	points[1] = Point;
}
