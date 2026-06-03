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

	void SetState(EState State);
	void SetShapeType(EShapeType ShapeType);

	void OnButtonDown(const POINT& Point);
	void OnMouseMove(const POINT& Point);
	void OnButtonUp(const POINT& Point);

private:
	std::shared_ptr<IShape> CreateShape(EShapeType ShapeType);
	void ResetState();

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

