#include "GDIManager.h"

bool GDIManager::Init()
{
	CHECK(CreateBrushes(), "브러쉬 생성 실패", false);
	CHECK(CreatePens(), "펜 생성 실패", false);

	LOG("GDI 매니저 초기화 성공");
	return true;
}

void GDIManager::Terminate()
{
	for (auto& [type, pen] : pens)
		if (pen)
			::DeleteObject(pen);
	pens.clear();

	for (auto& [type, brush] : brushes)
		if (brush)
			::DeleteObject(brush);
	brushes.clear();
}

RECT GDIManager::RenderBegin(HWND Wnd)
{
	::GetClientRect(Wnd, &rect);
	frontBuffer = ::GetDC(Wnd);

	backBuffer = ::CreateCompatibleDC(frontBuffer);
	bmp = ::CreateCompatibleBitmap(frontBuffer, rect.right - rect.left, rect.bottom - rect.top);
	old = static_cast<HBITMAP>(::SelectObject(backBuffer, bmp));
	::FillRect(backBuffer, &rect, static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH)));
	
	return rect;
}

void GDIManager::RenderEnd(HWND Wnd)
{
	::BitBlt(frontBuffer, 0, 0, rect.right - rect.left, rect.bottom - rect.top, backBuffer, 0, 0, SRCCOPY);
	::SelectObject(backBuffer, old);
	::DeleteObject(bmp);
	::DeleteDC(backBuffer);
	::ReleaseDC(Wnd, frontBuffer);
}

bool GDIManager::CreateBrushes()
{
	brushes[EBrushType::Red] = ::CreateSolidBrush(RGB(255, 0, 0));
	brushes[EBrushType::Green] = ::CreateSolidBrush(RGB(0, 255, 0));
	brushes[EBrushType::Blue] = ::CreateSolidBrush(RGB(0, 0, 255));
	brushes[EBrushType::Black] = ::CreateSolidBrush(RGB(0, 0, 0));
	brushes[EBrushType::White] = ::CreateSolidBrush(RGB(255, 255, 255));
	brushes[EBrushType::SelectBox] = static_cast<HBRUSH>(::GetStockObject(NULL_BRUSH));
	brushes[EBrushType::Selected] = static_cast<HBRUSH>(::GetStockObject(NULL_BRUSH));
	LOG("브러쉬 생성 성공");
	return true;
}

bool GDIManager::CreatePens()
{
	pens[EPenType::Red] = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pens[EPenType::Green] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pens[EPenType::Blue] = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pens[EPenType::Black] = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pens[EPenType::SelectBox] = ::CreatePen(PS_DOT, 1, RGB(0, 180, 0));
	pens[EPenType::Selected] = ::CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
	LOG("펜 생성 성공");
	return true;
}
