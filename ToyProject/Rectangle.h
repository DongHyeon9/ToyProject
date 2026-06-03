#pragma once
#include "Shape.h"

class CRectangle : public IShape
{
public:
	CRectangle() :IShape(EShapeType::Rect) {}
	bool CheckCollision(const POINT& pt) const override;
	void SetArea(const RECT& Rect) override;

	void SetRenctangle(const POINT& LT, const POINT& RB);
	void SetRenctangle(const RECT& Rect);
	void SetLeftTop(const POINT& LT);
	void SetRightBottom(const POINT& RB);
	void SetLeft(int32 Value);
	void SetTop(int32 Value);
	void SetRight(int32 Value);
	void SetBottom(int32 Value);

protected:
	void Render_Impl(HDC Buffer) override;
	void SelectedRender_Impl(HDC Buffer) override;

private:
	POINT lt{};
	POINT rb{};
};

