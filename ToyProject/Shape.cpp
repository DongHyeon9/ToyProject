#include "Shape.h"
#include "GDIManager.h"

IShape::IShape(EShapeType ShapeType) :shapeType{ ShapeType }
{
	static uint64 objID{};
	objectID = objID++;
}

void IShape::SelectedRender(HDC Buffer)
{
	HPEN oldPen = static_cast<HPEN>(::SelectObject(Buffer, GDIManager::GetInstance().GetPen(IsEditMode() ? EPenType::Edit : EPenType::Selected)));
	HBRUSH oldBrush = static_cast<HBRUSH>(::SelectObject(Buffer, GDIManager::GetInstance().GetBrush(IsEditMode() ? EBrushType::Edit : EBrushType::Selected)));

	Render_Impl(Buffer);

	::SelectObject(Buffer, oldPen);
	::SelectObject(Buffer, oldBrush);
}

void IShape::Render(HDC Buffer)
{
	HPEN oldPen = static_cast<HPEN>(::SelectObject(Buffer, GDIManager::GetInstance().GetPen(material.penType)));
	HBRUSH oldBrush = static_cast<HBRUSH>(::SelectObject(Buffer, GDIManager::GetInstance().GetBrush(material.brushType)));

	Render_Impl(Buffer);

	::SelectObject(Buffer, oldPen);
	::SelectObject(Buffer, oldBrush);
}

void IShape::SetRelativePoint(const POINT& Point)
{
	relativePoint = Point;
}
