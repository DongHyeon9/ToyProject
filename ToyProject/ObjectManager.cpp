#include "ObjectManager.h"
#include "Shape.h"
#include "Rectangle.h"

bool ObjectManager::Init()
{
	selectBox = std::make_shared<CRectangle>();
	selectBox->SetMaterial({ EPenType::SelectBox,EBrushType::SelectBox });
	LOG("오브젝트 매니저 초기화 성공");
	return true;
}

void ObjectManager::Render(HDC Buffer, RECT Rect)
{
	std::stable_sort(shapes.begin(), shapes.end(), [](const std::shared_ptr<IShape>& Lhs, const std::shared_ptr<IShape>& Rhs) {	return Lhs->GetZOrder() < Rhs->GetZOrder();	});

	for (const auto& shape : shapes)
		if (shape->IsSelected())
			shape->SelectedRender(Buffer);

	for (const auto& shape : shapes)
		shape->Render(Buffer);

	if (bSelecting)
		selectBox->Render(Buffer);
}

void ObjectManager::Terminate()
{

}

void ObjectManager::BeginSelectArea(const Point& pt)
{
	bSelecting = true;
	selectBox->SetRenctangle(pt, pt);
}

void ObjectManager::UpdateSelectArea(const Point& pt)
{
	selectBox->SetRightBottom(pt);
}

void ObjectManager::EndSelectArea()
{
	bSelecting = false;
}
