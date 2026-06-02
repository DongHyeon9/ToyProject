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
	void AddShape(std::shared_ptr<IShape> shape) { shapes.emplace_back(shape); }

	void BeginSelectArea(const Point& pt);
	void UpdateSelectArea(const Point& pt);
	void EndSelectArea();

private:
	std::vector<std::shared_ptr<IShape>> shapes{};
	std::shared_ptr<CRectangle> selectBox{};

	bool bSelecting{ false };
};

