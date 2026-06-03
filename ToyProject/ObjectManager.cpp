#include "ObjectManager.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Circle.h"
#include "Dot.h"
#include "Line.h"

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

	if (tempShape)
		tempShape->Render(Buffer);

	if (bSelecting && !tempShape)
		selectBox->Render(Buffer);
}

void ObjectManager::Terminate()
{

}

void ObjectManager::OnButtonDown(const POINT& Point, EState State, EShapeType ShapeType)
{
	state = State;
	shapeType = ShapeType;
	startPoint = Point;
	endPoint = Point;
	if (state == EState::Create)
	{
		tempShape = CreateShape(shapeType);
		tempShape->SetMaterial({ EPenType::TempShape, EBrushType::TempShape });
	}
	bSelecting = true;
	
}

void ObjectManager::OnMouseMove(const POINT& Point)
{
	if (bSelecting)
	{
		endPoint = Point;
		selectBox->SetRenctangle(startPoint, endPoint);
	}

	if (tempShape)
		tempShape->SetArea({ startPoint.x, startPoint.y, endPoint.x, endPoint.y });
}

void ObjectManager::OnButtonUp(const POINT& Point, EState State, EShapeType ShapeType)
{
	if (state == EState::Create)
	{
		tempShape->SetMaterial({ EngineUtil::RandomRange(EPenType::Black,EPenType::Blue),EngineUtil::RandomRange(EBrushType::Black,EBrushType::White) });
		shapes.emplace_back(std::move(tempShape));
	}
	else if (state == EState::Selected)
	{

	}
	else if (state == EState::None)
	{

	}
	state = State;
	shapeType = ShapeType;
	bSelecting = false;
}

std::shared_ptr<IShape> ObjectManager::CreateShape(EShapeType ShapeType)
{
	std::shared_ptr<IShape> result{};

	switch (ShapeType)
	{
	case EShapeType::Circle:	result = std::make_shared<CCircle>();		break;
	case EShapeType::Dot:		result = std::make_shared<CDot>();			break;
	case EShapeType::Line:		result = std::make_shared<CLine>();			break;
	case EShapeType::Polygon:	result = std::make_shared<CPolygon>();		break;
	case EShapeType::Rect:		result = std::make_shared<CRectangle>();	break;
	default:	assert(false);
	}

	return result;
}

