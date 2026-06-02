#pragma once
#include "Shape.h"

class CRectangle : public IShape
{
public:
	bool CheckCollision(const Point& pt) const override;
	void SetRenctangle(const Point& LT, const Point& RB);
	void SetRenctangle(const RECT& Rect);
	void SetLeftTop(const Point& LT);
	void SetRightBottom(const Point& RB);
	void SetLeft(int32 Value);
	void SetTop(int32 Value);
	void SetRight(int32 Value);
	void SetBottom(int32 Value);

protected:
	void Render_Impl(HDC Buffer) override;
	void SelectedRender_Impl(HDC Buffer) override;

private:
	Point lt{};
	Point rb{};
};

