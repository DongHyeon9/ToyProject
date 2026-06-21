#pragma once
#include "EngineCore.h"

class IShape;
class CRectangle;

class ObjectManager : public ISingleton<ObjectManager>
{
public:
	bool Init();
	void Render(HDC Buffer, RECT Rect);
	void Terminate();
	void AllDelete();
	void SelectDelete();
	void CancelSelect();
	void EnterMoveMode();
	void EnterEditMode();

	void SetState(EState State);
	void SetShapeType(EShapeType ShapeType);

	void OnButtonDown(const POINT& Point);
	void OnMouseMove(const POINT& Point);
	void OnButtonUp(const POINT& Point);

private:
	std::shared_ptr<IShape> CreateShape(EShapeType ShapeType);
	std::shared_ptr<IShape> FindShapeAt(const POINT& Point) const;
	bool CheckShapeAt(const std::shared_ptr<IShape>& Shape, const POINT& Point) const;
	void SelectShape(std::shared_ptr<IShape> Shape);
	void LogSelectedShapes() const;
	bool IsEditableShape(const std::shared_ptr<IShape>& Shape) const;
	void ExitEditMode(std::shared_ptr<IShape> Shape);
	void ResetState();
	void ResetInteractionState();

private:
	std::vector<std::shared_ptr<IShape>> shapes{};
	std::vector<std::shared_ptr<IShape>> selectedShapes{};
	std::shared_ptr<CRectangle> selectBox{};
	std::shared_ptr<IShape> tempShape{};

	EState state{};
	bool bMouseDown{};

	POINT startPoint{};
	POINT endPoint{};
};

