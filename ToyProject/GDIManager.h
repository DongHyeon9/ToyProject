#pragma once
#include "EngineCore.h"

class GDIManager : public ISingleton<GDIManager>
{
public:
	bool Init();
	void Terminate();
	RECT RenderBegin(HWND Wnd);
	void RenderEnd(HWND Wnd);

	HPEN GetPen(EPenType PenType) { return pens[PenType]; }
	HBRUSH GetBrush(EBrushType BrushType) { return brushes[BrushType]; }

	HDC GetBackBuffer() const { return backBuffer; }

private:
	bool CreateBrushes();
	bool CreatePens();

private:
	std::unordered_map<EBrushType, HBRUSH> brushes{};
	std::unordered_map<EPenType, HPEN> pens{};

	HDC backBuffer{};
	HDC frontBuffer{};
	RECT rect{};

	HBITMAP old{};
	HBITMAP bmp{};
};

