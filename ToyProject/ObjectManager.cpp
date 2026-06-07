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

	for (const auto& shape : selectedShapes)
		shape->SelectedRender(Buffer);

	for (const auto& shape : shapes)
		shape->Render(Buffer);

	if (state == EState::Create && bMouseDown)
		tempShape->Render(Buffer);

	if (state == EState::Selecting && bMouseDown)
		selectBox->Render(Buffer);
}

void ObjectManager::Terminate()
{

}

void ObjectManager::AllDelete()
{
	ResetState();
	selectedShapes.clear();
	shapes.clear();
}

void ObjectManager::SelectDelete()
{
	ResetState();

	std::set<uint64> objIDs{};

	for (const auto& shape : selectedShapes)
		objIDs.emplace(shape->GetObjectID());

	selectedShapes.clear();

	for (auto iter = shapes.begin(); iter != shapes.end();)
		if (objIDs.contains((*iter)->GetObjectID()))
			iter = shapes.erase(iter);
		else
			++iter;
}

void ObjectManager::CancelSelect()
{
	ResetState();
	selectedShapes.clear();
}

void ObjectManager::SetState(EState State)
{
	state = State;
}

void ObjectManager::SetShapeType(EShapeType ShapeType)
{
	tempShape = CreateShape(ShapeType);
	tempShape->SetMaterial({ EPenType::TempShape, EBrushType::TempShape });
}

void ObjectManager::OnButtonDown(const POINT& Point)
{
	startPoint = Point;
	endPoint = Point;
	if (state == EState::Create) {}
	else if (state == EState::None)
	{
		if (selectedShapes.size() == 1)
		{
			state = selectedShapes[0]->GetState();
		}
		else if (selectedShapes.empty())
		{
			selectBox = std::make_shared<CRectangle>();
			selectBox->SetMaterial({ EPenType::SelectBox, EBrushType::SelectBox });
			state = EState::Selecting;
		}
		else
		{
			state = EState::Move;
		}
	}
	else if (state == EState::Selecting) {}
	else if (state == EState::Move) {}
	else if (state == EState::Edit) {}

	bMouseDown = true;
}

void ObjectManager::OnMouseMove(const POINT& Point)
{
	if (!bMouseDown) return;
	endPoint = Point;

	if (state == EState::Create)
	{
		tempShape->SetArea({ startPoint.x, startPoint.y, endPoint.x, endPoint.y });
	}
	else if (state == EState::None) {}
	else if (state == EState::Selecting)
	{
		selectBox->SetRenctangle(startPoint, endPoint);
	}
	else if (state == EState::Move)
	{
		for (auto& shape : selectedShapes)
			shape->SetRelativePoint(startPoint - endPoint);
	}
	else if (state == EState::Edit)
	{
		for (auto& shape : selectedShapes)
			shape->SetRelativePoint(startPoint - endPoint);
	}		
}

void ObjectManager::OnButtonUp(const POINT& Point)
{
	if (state == EState::Create)
	{
		tempShape->SetMaterial({ EngineUtil::RandomRange(EPenType::Black,EPenType::Blue),EngineUtil::RandomRange(EBrushType::Black,EBrushType::White) });
		shapes.emplace_back(tempShape);
	}
	else if (state == EState::None)
	{
	}
	else if (state == EState::Selecting)
	{
		for (const auto& shape : shapes)
		{
			if (shape->CheckOverlap(selectBox))
			{
				shape->CandidateEditPoint(selectBox);
				selectedShapes.emplace_back(shape);
			}
		}
	}
	else if (state == EState::Move)
	{
		for (auto& shape : selectedShapes)
		{
			shape->AddCoordinate(endPoint - startPoint);
			shape->SetRelativePoint(POINT{});
		}
	}
	else if (state == EState::Edit)
	{
		for (auto& shape : selectedShapes)
		{
			shape->ConfirmEdit();
		}
	}

	bMouseDown = false;
	ResetState();
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

void ObjectManager::ResetState()
{
	tempShape.reset();
	selectBox.reset();
	state = EState::None;
}

