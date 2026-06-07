#pragma once
#include "Shape.h"

class CLine : public IShape
{
public:
	CLine() :IShape(EShapeType::Line) {}

	void SetArea(const RECT& Rect) override;
	bool CheckOverlap(std::shared_ptr<IShape> Rhs) const override;
	bool CheckOverlap(const POINT& Point) const override;
	EState GetState() const override;
	void AddCoordinate(const POINT& Point) override;
	void CandidateEditPoint(std::shared_ptr<IShape> Rect) override;
	void ConfirmEdit() override;

	void SetStart(const POINT& Point);
	void SetEnd(const POINT& Point);

	const std::array<POINT, 2>& GetPoints()const { return points; }

protected:
	void Render_Impl(HDC Buffer) override;

private:
	std::array<POINT, 2> points{};

	std::vector<size_t> editPointIdx{};
};

