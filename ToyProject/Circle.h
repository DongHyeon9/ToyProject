#pragma once
#include "Shape.h"

class CCircle : public IShape
{
public:
	CCircle() :IShape(EShapeType::Circle) {}
	
	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	bool CheckOverlap(const POINT& Point) const override;
	EState GetState() const override;
	void AddCoordinate(const POINT& Point) override;
	void CandidateEditPoint(std::shared_ptr<IShape> Rect) override;
	void ConfirmEdit() override;

	void SetCenter(const POINT& Point);
	void SetRadius(int32 Radius);

	const POINT& GetCenter()const { return center; }
	int32 GetRadius()const { return radius; }

protected:
	void Render_Impl(HDC Buffer) override;

private:
	POINT center{};
	int32 radius{};
};

