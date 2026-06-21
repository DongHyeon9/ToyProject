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
		shape->Render(Buffer);

	for (const auto& shape : selectedShapes)
		shape->SelectedRender(Buffer);

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
	for (auto& shape : selectedShapes)
		ExitEditMode(shape);
	selectedShapes.clear();
	shapes.clear();
}

void ObjectManager::SelectDelete()
{
	ResetState();

	std::set<uint64> objIDs{};

	for (const auto& shape : selectedShapes)
		objIDs.emplace(shape->GetObjectID());

	for (auto& shape : selectedShapes)
		ExitEditMode(shape);
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
	for (auto& shape : selectedShapes)
		ExitEditMode(shape);
	selectedShapes.clear();
}

void ObjectManager::EnterMoveMode()
{
	if (selectedShapes.empty())
	{
		::MessageBox(nullptr, TEXT("이동모드는 도형이 선택된 상태에서만 가능합니다."), TEXT("이동모드"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	for (auto& shape : selectedShapes)
		ExitEditMode(shape);
	state = EState::Move;
}
void ObjectManager::EnterEditMode()
{
	if (selectedShapes.empty())
	{
		::MessageBox(nullptr, TEXT("편집모드는 도형이 선택된 상태에서만 가능합니다."), TEXT("편집모드"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	bool bHasEditableShape = false;
	for (auto& shape : selectedShapes)
	{
		if (!IsEditableShape(shape))
			continue;

		shape->SetEditMode(true);
		bHasEditableShape = true;
	}

	if (!bHasEditableShape)
	{
		::MessageBox(nullptr, TEXT("선택된 도형 중 편집 가능한 도형이 없습니다."), TEXT("편집모드"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	state = EState::Edit;
}
void ObjectManager::SetState(EState State)
{
	state = State;
}

void ObjectManager::SetShapeType(EShapeType ShapeType)
{
	for (auto& shape : selectedShapes)
		ExitEditMode(shape);
	selectedShapes.clear();
	tempShape = CreateShape(ShapeType);
	tempShape->SetMaterial({ EPenType::TempShape, EBrushType::TempShape });
}

void ObjectManager::OnButtonDown(const POINT& Point)
{
	startPoint = Point;
	endPoint = Point;

	if (state == EState::Create)
	{
	}
	else if (state == EState::Move)
	{
		if (selectedShapes.empty())
			state = EState::Idle;
	}
	else if (state == EState::Edit)
	{
		// Edit 상태에서는 드래그가 크기 조절로 동작
	}
	else if (state == EState::Idle)
	{
		if (std::shared_ptr<IShape> pickedShape = FindShapeAt(Point))
		{
			SelectShape(pickedShape);
		}
		else
		{
			CancelSelect();
			selectBox = std::make_shared<CRectangle>();
			selectBox->SetMaterial({ EPenType::SelectBox, EBrushType::SelectBox });
			selectBox->SetRenctangle(startPoint, endPoint);
			state = EState::Selecting;
		}
	}

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
	else if (state == EState::Idle) {}
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
		const POINT delta = Point - startPoint;
		for (auto& shape : selectedShapes)
		{
			if (shape->IsEditMode())
				shape->Resize(delta);
		}
		startPoint = Point;
	}		
}

void ObjectManager::OnButtonUp(const POINT& Point)
{
	if (state == EState::Create)
	{
		tempShape->SetMaterial({ EngineUtil::RandomRange(EPenType::Black,EPenType::Blue),EngineUtil::RandomRange(EBrushType::Red,EBrushType::Black) });
		shapes.emplace_back(tempShape);
		ResetInteractionState();
	}
	else if (state == EState::Selecting)
	{
		selectBox->SetRenctangle(startPoint, endPoint);
		selectedShapes.clear();
		for (const auto& shape : shapes)
		{
			if (shape->CheckOverlap(selectBox))
				selectedShapes.emplace_back(shape);
		}
		ResetInteractionState();
		LogSelectedShapes();
	}
	else if (state == EState::Move)
	{
		for (auto& shape : selectedShapes)
		{
			shape->AddCoordinate(endPoint - startPoint);
			shape->SetRelativePoint(POINT{});
		}
	}

	bMouseDown = false;
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

std::shared_ptr<IShape> ObjectManager::FindShapeAt(const POINT& Point) const
{
	for (auto iter = shapes.rbegin(); iter != shapes.rend(); ++iter)
	{
		if (CheckShapeAt(*iter, Point))
			return *iter;
	}

	return nullptr;
}

bool ObjectManager::CheckShapeAt(const std::shared_ptr<IShape>& Shape, const POINT& Point) const
{
	if (!Shape)
		return false;

	switch (Shape->GetShapeType())
	{
	case EShapeType::Rect:
	{
		const auto rect = std::static_pointer_cast<CRectangle>(Shape);
		int32 xMin = rect->GetPoints()[0].x;
		int32 xMax = rect->GetPoints()[0].x;
		int32 yMin = rect->GetPoints()[0].y;
		int32 yMax = rect->GetPoints()[0].y;

		for (const auto& rectPoint : rect->GetPoints())
		{
			xMin = min(xMin, rectPoint.x);
			xMax = max(xMax, rectPoint.x);
			yMin = min(yMin, rectPoint.y);
			yMax = max(yMax, rectPoint.y);
		}

		return Point.x >= xMin - PICK_TOLERANCE && Point.x <= xMax + PICK_TOLERANCE
			&& Point.y >= yMin - PICK_TOLERANCE && Point.y <= yMax + PICK_TOLERANCE;
	}
	default:
		return Shape->CheckOverlap(Point);
	}
}
void ObjectManager::SelectShape(std::shared_ptr<IShape> Shape)
{
	const bool bKeepCurrentEditShape = selectedShapes.size() == 1 && Shape
		&& selectedShapes[0]->GetObjectID() == Shape->GetObjectID()
		&& selectedShapes[0]->IsEditMode();

	if (!bKeepCurrentEditShape)
	{
		for (auto& selectedShape : selectedShapes)
			ExitEditMode(selectedShape);
		selectedShapes.clear();
		state = EState::Idle;
	}

	if (Shape && selectedShapes.empty())
	{
		selectedShapes.emplace_back(Shape);
		LogSelectedShapes();
	}
}
void ObjectManager::LogSelectedShapes() const
{
	for (const auto& shape : selectedShapes)
	{
		if (shape)
			shape->LogInfo();
	}
}
bool ObjectManager::IsEditableShape(const std::shared_ptr<IShape>& Shape) const
{
	if (!Shape)
		return false;

	const EShapeType shapeType = Shape->GetShapeType();
	return shapeType != EShapeType::None;
}

void ObjectManager::ExitEditMode(std::shared_ptr<IShape> Shape)
{
	if (!Shape)
		return;

	Shape->ConfirmEdit();
	Shape->SetEditMode(false);
}

void ObjectManager::ResetState()
{
	tempShape.reset();
	selectBox.reset();
	state = EState::Idle;
}

void ObjectManager::ResetInteractionState()
{
	tempShape.reset();
	selectBox.reset();
	state = std::any_of(selectedShapes.begin(), selectedShapes.end(), [](const std::shared_ptr<IShape>& Shape) { return Shape->IsEditMode(); }) ? EState::Edit : EState::Idle;
}

