#pragma once
#include "Shape.h"

// 이름은 폴리곤이지만 삼각형이다
class CPolygon : public IShape
{
public:
	CPolygon() :IShape(EShapeType::Polygon) {}

	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	EState GetState() const override;
	void EditShape(const RECT& Rect) override;
	void ConfirmEdit() override;
	void AddCoordinate(const POINT& Point) override;

	void SetPolygon(const std::array<POINT, 3>& Points);
	void SetPoint(const POINT& Point, int32 Idx);

protected:
	void Render_Impl(HDC Buffer) override;

private:
	std::array<POINT, 3> points{};
};
