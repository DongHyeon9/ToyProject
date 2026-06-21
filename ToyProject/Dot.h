#pragma once
#include "Shape.h"

class CDot : public IShape
{
public:
	CDot() :IShape(EShapeType::Dot) {}
	
	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<const IShape> Rhs) const override;
	bool CheckOverlap(const POINT& Point) const override;
	EState GetState() const override;
	void AddCoordinate(const POINT& Point) override;
	void ConfirmEdit() override;
	void LogInfo() const override;

	void SetPoint(const POINT& Point);

	const POINT& GetPoint()const { return point; }

protected:
	void Render_Impl(HDC Buffer) override;

private:
	POINT point{};

	static constexpr int32 SIZE{ 3 };
	static constexpr int32 SIZE_SELECTED{ 5 };
};

