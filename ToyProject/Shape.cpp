#include "Shape.h"
#include "GDIManager.h"

void IShape::SelectedRender(HDC Buffer)
{
	HPEN oldPen = static_cast<HPEN>(::SelectObject(Buffer, GDIManager::GetInstance().GetPen(EPenType::Selected)));
	HBRUSH oldBrush = static_cast<HBRUSH>(::SelectObject(Buffer, GDIManager::GetInstance().GetBrush(EBrushType::Selected)));

	SelectedRender_Impl(Buffer);

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
