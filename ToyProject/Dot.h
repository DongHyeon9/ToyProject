#pragma once
#include "Shape.h"

class CDot : public IShape
{
public:
	CDot() :IShape(EShapeType::Dot) {}
	bool CheckCollision(const POINT& pt) const override;
	void SetArea(const RECT& Rect) override;

	void SetPoint(const POINT& Point);

protected:
	void Render_Impl(HDC Buffer) override;
	void SelectedRender_Impl(HDC Buffer) override;

private:
	POINT point{};

	static constexpr int32 SIZE{ 3 };
	static constexpr int32 SIZE_SELECTED{ 5 };
};

