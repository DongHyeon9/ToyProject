#pragma once
#include "Shape.h"

class CRectangle : public IShape
{
public:
	CRectangle() :IShape(EShapeType::Rect) {}
	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<const IShape> Rhs) const override;
	bool CheckOverlap(const POINT& Point) const override;
	EState GetState() const override;
	void AddCoordinate(const POINT& Point) override;
	void CandidateEditPoint(std::shared_ptr<IShape> Rect) override;
	void ConfirmEdit() override;

	void SetRenctangle(const POINT& LT, const POINT& RB);
	void SetRenctangle(const RECT& Rect);

	const std::array<POINT, 4>& GetPoints()const { return points; }

protected:
	void Render_Impl(HDC Buffer) override;

private:
	std::array<POINT, 4> points{};
	std::vector<size_t> editPointIdx{};
};
