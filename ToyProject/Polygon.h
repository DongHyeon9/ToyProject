#pragma once
#include "Shape.h"

// 이름은 폴리곤이지만 삼각형이다
class CPolygon : public IShape
{
public:
	CPolygon() :IShape(EShapeType::Polygon) {}
	bool CheckCollision(const POINT& pt) const override;
	void SetArea(const RECT& Rect) override;

	void SetPolygon(const std::array<POINT, 3>& Points);
	void SetPoint(const POINT& Point, int32 Idx);

protected:
	void Render_Impl(HDC Buffer) override;
	void SelectedRender_Impl(HDC Buffer) override;

private:
	std::array<POINT, 3> points{};
};
