#pragma once
#include "Shape.h"

class CCircle : public IShape
{
public:
	CCircle() :IShape(EShapeType::Circle) {}
	bool CheckCollision(const POINT& pt) const override;
	void SetArea(const RECT& Rect) override;

	void SetCenter(const POINT& Point);
	void SetRadius(int32 Radius);

protected:
	void Render_Impl(HDC Buffer) override;
	void SelectedRender_Impl(HDC Buffer) override;

private:
	POINT center{};
	int32 radius{};
};

