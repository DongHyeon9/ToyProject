#pragma once
#include "Shape.h"

class CCircle : public IShape
{
public:
	CCircle() :IShape(EShapeType::Circle) {}
	
	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	EState GetState() const override;
	void EditShape(const RECT& Rect) override;
	void ConfirmEdit() override;
	void AddCoordinate(const POINT& Point) override;

	void SetCenter(const POINT& Point);
	void SetRadius(int32 Radius);

protected:
	void Render_Impl(HDC Buffer) override;

private:
	POINT center{};
	int32 radius{};
};

