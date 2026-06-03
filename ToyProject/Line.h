#pragma once
#include "Shape.h"

class CLine : public IShape
{
public:
	CLine() :IShape(EShapeType::Line) {}

	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	EState GetState() const override;
	void EditShape(const RECT& Rect) override;
	void ConfirmEdit() override;
	void AddCoordinate(const POINT& Point) override;

	void SetStart(const POINT& Point);
	void SetEnd(const POINT& Point);

protected:
	void Render_Impl(HDC Buffer) override;

private:
	POINT start{};
	POINT end{};

};

