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
	void AllDelete() { shapes.clear(); }

	void OnButtonDown(const POINT& Point, EState State, EShapeType ShapeType);
	void OnMouseMove(const POINT& Point);
	void OnButtonUp(const POINT& Point, EState State, EShapeType ShapeType);

private:
	std::shared_ptr<IShape> CreateShape(EShapeType ShapeType);

private:
	std::vector<std::shared_ptr<IShape>> shapes{};
	std::shared_ptr<CRectangle> selectBox{};
	std::shared_ptr<IShape> tempShape{};

	bool bSelecting{ false };
	EState state{};
	EShapeType shapeType{};

	POINT startPoint{};
	POINT endPoint{};
};

