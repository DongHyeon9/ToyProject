#include "Util.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Line.h"
#include "Dot.h"
#include "Circle.h"

// https://kareus.tistory.com/15
// https://github.com/Kareus/SP2C/blob/main/src/SP2C/SPC_Collision.cpp

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CRectangle> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CPolygon> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CLine> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CRectangle> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CPolygon> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CLine> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CPolygon> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CLine> Lhs, std::shared_ptr<const CLine> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CLine> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CLine> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CDot> Lhs, std::shared_ptr<const CDot> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CDot> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	return true;
}

bool EngineUtil::IsOverlap(std::shared_ptr<const CCircle> Lhs, std::shared_ptr<const CCircle> Rhs)
{
	return true;
}
