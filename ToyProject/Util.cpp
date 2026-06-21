#include "Util.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Line.h"
#include "Dot.h"
#include "Circle.h"

namespace
{
	RECT GetBounds(const std::array<POINT, 4>& Points)
	{
		RECT result{ Points[0].x, Points[0].y, Points[0].x, Points[0].y };
		for (const auto& point : Points)
		{
			result.left = min(result.left, point.x);
			result.top = min(result.top, point.y);
			result.right = max(result.right, point.x);
			result.bottom = max(result.bottom, point.y);
		}
		return result;
	}

	bool Contains(const RECT& Rect, const POINT& Point)
	{
		return Point.x >= Rect.left && Point.x <= Rect.right && Point.y >= Rect.top && Point.y <= Rect.bottom;
	}

	double DistanceSquared(const POINT& Lhs, const POINT& Rhs)
	{
		const double dx = static_cast<double>(Lhs.x - Rhs.x);
		const double dy = static_cast<double>(Lhs.y - Rhs.y);
		return dx * dx + dy * dy;
	}

	double DistancePointToSegmentSquared(const POINT& Point, const POINT& Start, const POINT& End)
	{
		const double dx = static_cast<double>(End.x - Start.x);
		const double dy = static_cast<double>(End.y - Start.y);
		const double lengthSquared = dx * dx + dy * dy;

		if (lengthSquared <= EPSILON)
			return DistanceSquared(Point, Start);

		const double t = std::clamp(((Point.x - Start.x) * dx + (Point.y - Start.y) * dy) / lengthSquared, 0.0, 1.0);
		const double closestX = Start.x + t * dx;
		const double closestY = Start.y + t * dy;
		const double distanceX = Point.x - closestX;
		const double distanceY = Point.y - closestY;
		return distanceX * distanceX + distanceY * distanceY;
	}

	int32 Sign(double Value)
	{
		if (Value > EPSILON)
			return 1;
		if (Value < -EPSILON)
			return -1;
		return 0;
	}

	bool IsOnSegment(const POINT& Point, const POINT& Start, const POINT& End)
	{
		return Sign(EngineUtil::CrossProduct(Start, End, Point)) == 0
			&& Point.x >= min(Start.x, End.x) && Point.x <= max(Start.x, End.x)
			&& Point.y >= min(Start.y, End.y) && Point.y <= max(Start.y, End.y);
	}

	bool IsSegmentIntersect(const POINT& A, const POINT& B, const POINT& C, const POINT& D)
	{
		const int32 abC = Sign(EngineUtil::CrossProduct(A, B, C));
		const int32 abD = Sign(EngineUtil::CrossProduct(A, B, D));
		const int32 cdA = Sign(EngineUtil::CrossProduct(C, D, A));
		const int32 cdB = Sign(EngineUtil::CrossProduct(C, D, B));

		if (abC == 0 && IsOnSegment(C, A, B)) return true;
		if (abD == 0 && IsOnSegment(D, A, B)) return true;
		if (cdA == 0 && IsOnSegment(A, C, D)) return true;
		if (cdB == 0 && IsOnSegment(B, C, D)) return true;

		return abC * abD < 0 && cdA * cdB < 0;
	}

	template<size_t Count>
	bool HasIntersectingEdges(const std::array<POINT, Count>& Lhs, const std::array<POINT, Count>& Rhs)
	{
		for (size_t i = 0; i < Count; ++i)
		{
			const POINT lhsStart = Lhs[i];
			const POINT lhsEnd = Lhs[(i + 1) % Count];
			for (size_t j = 0; j < Count; ++j)
			{
				const POINT rhsStart = Rhs[j];
				const POINT rhsEnd = Rhs[(j + 1) % Count];
				if (IsSegmentIntersect(lhsStart, lhsEnd, rhsStart, rhsEnd))
					return true;
			}
		}
		return false;
	}

	bool RectIntersectsLine(const RECT& Rect, const POINT& Start, const POINT& End)
	{
		if (Contains(Rect, Start) || Contains(Rect, End))
			return true;

		const std::array<POINT, 4> rectPoints{
			POINT{ Rect.left, Rect.top }, POINT{ Rect.right, Rect.top },
			POINT{ Rect.right, Rect.bottom }, POINT{ Rect.left, Rect.bottom }
		};

		for (size_t i = 0; i < rectPoints.size(); ++i)
		{
			if (IsSegmentIntersect(Start, End, rectPoints[i], rectPoints[(i + 1) % rectPoints.size()]))
				return true;
		}

		return false;
	}
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CRectangle> Rhs)
{
	const RECT lhsBounds = GetBounds(Lhs->GetPoints());
	const RECT rhsBounds = GetBounds(Rhs->GetPoints());
	return lhsBounds.left <= rhsBounds.right && lhsBounds.right >= rhsBounds.left
		&& lhsBounds.top <= rhsBounds.bottom && lhsBounds.bottom >= rhsBounds.top;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CPolygon> Rhs)
{
	const RECT rect = GetBounds(Lhs->GetPoints());
	const auto& polyPoints = Rhs->GetPoints();
	for (const auto& point : polyPoints)
		if (Contains(rect, point))
			return true;

	for (const auto& point : Lhs->GetPoints())
		if (Rhs->CheckOverlap(point))
			return true;

	for (size_t i = 0; i < polyPoints.size(); ++i)
		if (RectIntersectsLine(rect, polyPoints[i], polyPoints[(i + 1) % polyPoints.size()]))
			return true;

	return false;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CLine> Rhs)
{
	const auto& points = Rhs->GetPoints();
	return RectIntersectsLine(GetBounds(Lhs->GetPoints()), points[0], points[1]);
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return Contains(GetBounds(Lhs->GetPoints()), Rhs->GetPoint());
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	const RECT rect = GetBounds(Lhs->GetPoints());
	const POINT center = Rhs->GetCenter();
	const int32 closestX = std::clamp(center.x, rect.left, rect.right);
	const int32 closestY = std::clamp(center.y, rect.top, rect.bottom);
	return DistanceSquared(center, POINT{ closestX, closestY }) <= static_cast<double>(Rhs->GetRadius()) * Rhs->GetRadius();
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CPolygon> Rhs)
{
	for (const auto& point : Lhs->GetPoints())
		if (Rhs->CheckOverlap(point))
			return true;
	for (const auto& point : Rhs->GetPoints())
		if (Lhs->CheckOverlap(point))
			return true;

	const auto& lhsPoints = Lhs->GetPoints();
	const auto& rhsPoints = Rhs->GetPoints();
	for (size_t i = 0; i < lhsPoints.size(); ++i)
		for (size_t j = 0; j < rhsPoints.size(); ++j)
			if (IsSegmentIntersect(lhsPoints[i], lhsPoints[(i + 1) % lhsPoints.size()], rhsPoints[j], rhsPoints[(j + 1) % rhsPoints.size()]))
				return true;

	return false;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CLine> Rhs)
{
	const auto& linePoints = Rhs->GetPoints();
	if (Lhs->CheckOverlap(linePoints[0]) || Lhs->CheckOverlap(linePoints[1]))
		return true;

	const auto& polyPoints = Lhs->GetPoints();
	for (size_t i = 0; i < polyPoints.size(); ++i)
		if (IsSegmentIntersect(linePoints[0], linePoints[1], polyPoints[i], polyPoints[(i + 1) % polyPoints.size()]))
			return true;

	return false;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return Lhs->CheckOverlap(Rhs->GetPoint());
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	if (Lhs->CheckOverlap(Rhs->GetCenter()))
		return true;

	const double radiusSquared = static_cast<double>(Rhs->GetRadius()) * Rhs->GetRadius();
	const auto& points = Lhs->GetPoints();
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (DistanceSquared(points[i], Rhs->GetCenter()) <= radiusSquared)
			return true;
		if (DistancePointToSegmentSquared(Rhs->GetCenter(), points[i], points[(i + 1) % points.size()]) <= radiusSquared)
			return true;
	}

	return false;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CLine> Lhs, std::shared_ptr<const CLine> Rhs)
{
	const auto& lhsPoints = Lhs->GetPoints();
	const auto& rhsPoints = Rhs->GetPoints();
	return IsSegmentIntersect(lhsPoints[0], lhsPoints[1], rhsPoints[0], rhsPoints[1]);
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CLine> Lhs, std::shared_ptr<const CDot> Rhs)
{
	const auto& points = Lhs->GetPoints();
	return DistancePointToSegmentSquared(Rhs->GetPoint(), points[0], points[1]) <= PICK_TOLERANCE * PICK_TOLERANCE;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CLine> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	const auto& points = Lhs->GetPoints();
	return DistancePointToSegmentSquared(Rhs->GetCenter(), points[0], points[1]) <= static_cast<double>(Rhs->GetRadius()) * Rhs->GetRadius();
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CDot> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return DistanceSquared(Lhs->GetPoint(), Rhs->GetPoint()) <= PICK_TOLERANCE * PICK_TOLERANCE;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CDot> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	return DistanceSquared(Lhs->GetPoint(), Rhs->GetCenter()) <= static_cast<double>(Rhs->GetRadius()) * Rhs->GetRadius();
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CCircle> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	const double radiusSum = static_cast<double>(Lhs->GetRadius() + Rhs->GetRadius());
	return DistanceSquared(Lhs->GetCenter(), Rhs->GetCenter()) <= radiusSum * radiusSum;
}