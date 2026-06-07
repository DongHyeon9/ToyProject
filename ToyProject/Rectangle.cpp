#include "Rectangle.h"

void CRectangle::Render_Impl(HDC Buffer)
{
	std::array<POINT, 4> finalPoints{ points };
	const POINT relativePoint = GetRelativePoint();

	if (editPointIdx.empty())
	{
		for (auto& point : finalPoints)
			point -= relativePoint;
	}
	else
	{
		for (auto idx : editPointIdx)
			finalPoints[idx] -= relativePoint;
	}

	// 점 별로 컨트롤 하기 위해 Rectangle -> Polygon으로 변경
	::Polygon(Buffer, finalPoints.data(), static_cast<int32>(finalPoints.size()));
}

void CRectangle::SetArea(const RECT& Rect)
{
	SetRenctangle(Rect);
}

bool CRectangle::CheckOverlap(std::shared_ptr<IShape> Rhs) const
{
	const EShapeType rhsShapeType{ Rhs->GetShapeType() };

	switch (rhsShapeType)
	{
	case EShapeType::Rect:		return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(shared_from_this()), std::static_pointer_cast<CRectangle>(Rhs));
	case EShapeType::Circle:	return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(shared_from_this()), std::static_pointer_cast<CCircle>(Rhs));
	case EShapeType::Dot:		return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(shared_from_this()), std::static_pointer_cast<CDot>(Rhs));
	case EShapeType::Line:		return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(shared_from_this()), std::static_pointer_cast<CLine>(Rhs));
	case EShapeType::Polygon:	return EngineUtil::IsOverlap(std::static_pointer_cast<CRectangle>(shared_from_this()), std::static_pointer_cast<CPolygon>(Rhs));

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
		yMin = max(yMin, point.y);
	}
	POINT leftTop{ xMin, yMin };
	POINT rightBottom{ xMax, yMax };
	return Point.x >= xMin && Point.y >= yMin && Point.x <= xMax && Point.y <= yMax;
}

EState CRectangle::GetState() const
{
	return editPointIdx.empty() ? EState::Move : EState::Edit;
}

void CRectangle::AddCoordinate(const POINT& Point)
{
	for (auto& point : points)
		point += Point;
}

void CRectangle::CandidateEditPoint(std::shared_ptr<IShape> Rect)
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (Rect->CheckOverlap(points[i]))
			editPointIdx.emplace_back(i);
	}
}

void CRectangle::ConfirmEdit()
{
	SetRelativePoint(POINT{});
	editPointIdx.clear();
}

void CRectangle::SetRenctangle(const POINT& LT, const POINT& RB)
{
	// 좌측 상단
	points[0].x = LT.x;
	points[0].y = LT.y;

	// 우측 상단
	points[1].x = RB.x;
	points[1].y = LT.y;

	// 우측 하단
	points[2].x = RB.x;
	points[2].y = RB.y;

	// 좌측 하단
	points[3].x = LT.x;
	points[3].y = RB.y;
}

void CRectangle::SetRenctangle(const RECT& Rect)
{
	SetRenctangle({ Rect.left,Rect.top }, { Rect.right,Rect.bottom });
}

