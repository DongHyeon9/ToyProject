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
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(Rhs), std::static_pointer_cast<CPolygon>(shared_from_this()));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<CPolygon>(shared_from_this()), std::static_pointer_cast<CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<CPolygon>(shared_from_this()), std::static_pointer_cast<CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<CPolygon>(shared_from_this()), std::static_pointer_cast<CLine>(Rhs));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<CPolygon>(shared_from_this()), std::static_pointer_cast<CPolygon>(Rhs));

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
	return editPointIdx.empty() ? EState::Move : EState::Edit;
}

void CPolygon::AddCoordinate(const POINT& Point)
{
	for (auto& point : points)
		point += Point;
}

void CPolygon::CandidateEditPoint(std::shared_ptr<IShape> Rect)
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (Rect->CheckOverlap(points[i]))
			editPointIdx.emplace_back(i);
	}
}

void CPolygon::ConfirmEdit()
{
	SetRelativePoint(POINT{});
	editPointIdx.clear();
}

void CPolygon::SetPolygon(const std::array<POINT, 3>& Points)
{
	points = Points;
}

void CPolygon::SetPoint(const POINT& Point, int32 Idx)
{
	points[Idx] = Point;
}
