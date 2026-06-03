#pragma once
#include "Shape.h"

class CDot : public IShape
{
public:
	CDot() :IShape(EShapeType::Dot) {}
	
	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	EState GetState() const override;
	void EditShape(const RECT& Rect) override;
	void ConfirmEdit() override;
	void AddCoordinate(const POINT& Point) override;

	void SetPoint(const POINT& Point);

protected:
	void Render_Impl(HDC Buffer) override;

private:
	POINT point{};

	static constexpr int32 SIZE{ 3 };
	static constexpr int32 SIZE_SELECTED{ 5 };
};

