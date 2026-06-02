#pragma once
#include "Shape.h"

class CTriangle : public IShape
{
public:
	bool CheckCollision(const Point& pt) const override;

protected:
	void Render_Impl(HDC Buffer) override;
	void SelectedRender_Impl(HDC Buffer) override;

};

