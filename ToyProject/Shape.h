#pragma once
#include "EngineCore.h"

class CRectangle;

class IShape : public std::enable_shared_from_this<IShape>
{
public:
	IShape(EShapeType ShapeType);
	virtual ~IShape() = default;
	void SelectedRender(HDC Buffer);
	void Render(HDC Buffer);
	void SetMaterial(Material NewMaterial) { material = NewMaterial; }

	virtual void SetArea(const RECT& Rect) = 0;
	virtual bool CheckOverlap(std::shared_ptr<const IShape> Rhs) const = 0;
	virtual bool CheckOverlap(const POINT& Point) const = 0;
	virtual EState GetState() const = 0;
	virtual void AddCoordinate(const POINT& Point) = 0;
	virtual void CandidateEditPoint(std::shared_ptr<IShape> Rect) = 0;
	virtual void ConfirmEdit() = 0;
	
	void SetRelativePoint(const POINT& Point);
	POINT GetRelativePoint()const { return relativePoint; }
	int32 GetZOrder() const { return ZOrder; }
	bool IsSelected() const { return isSelected; }
	void SetSelected(bool selected) { isSelected = selected; }
	EShapeType GetShapeType() const { return shapeType; }
	uint64 GetObjectID() const { return objectID; }

protected:
	virtual void Render_Impl(HDC) = 0;

private:
	int32 ZOrder{ ZOrder::NONE };
	bool isSelected{ false };
	Material material{};
	EShapeType shapeType{};
	uint64 objectID{};
	POINT relativePoint{};
};

