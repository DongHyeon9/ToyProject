#pragma once
#include "Shape.h"

class CRectangle : public IShape
{
public:
	CRectangle() :IShape(EShapeType::Rect) {}
	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	EState GetState() const override;
	void EditShape(const RECT& Rect) override;
	void ConfirmEdit() override;
	void AddCoordinate(const POINT& Point) override;

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

private:
	POINT lt{};
	POINT rb{};
};

