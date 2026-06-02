#pragma once
#include "EngineCore.h"

class IShape
{
public:
	virtual ~IShape() = default;
	void SelectedRender(HDC Buffer);
	void Render(HDC Buffer);
	void SetMaterial(Material NewMaterial) { material = NewMaterial; }
	virtual bool CheckCollision(const Point& pt) const = 0;

	int32 GetZOrder() const { return ZOrder; }
	bool IsSelected() const { return isSelected; }
	void SetSelected(bool selected) { isSelected = selected; }

protected:
	virtual void Render_Impl(HDC) = 0;
	virtual void SelectedRender_Impl(HDC) = 0;

private:
	int32 ZOrder{ ZOrder::NONE };
	bool isSelected{ false };
	Material material{};
};

