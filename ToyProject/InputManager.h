#pragma once
#include "EngineCore.h"

class InputManager : public ISingleton<InputManager>
{
public:
	bool Init();
	void Terminate();
	LRESULT WinProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam);

private:
	bool RegisterMessage();
	bool RegisterCommand();

#pragma region 메세지 처리 함수
	LRESULT OnCommand(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonUp(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnSize(HWND Wnd, WPARAM wParam, LPARAM lParam);
#pragma endregion

#pragma region 커맨드 처리 함수
	LRESULT OnExit(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnAllDelete(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDot(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnLine(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnCircle(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnTriangle(HWND Wnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnRect(HWND Wnd, WPARAM wParam, LPARAM lParam);
#pragma endregion

private:
	std::unordered_map<UINT, std::function<LRESULT(HWND, WPARAM, LPARAM)>> messageLUT{};
	std::unordered_map<UINT, std::function<LRESULT(HWND, WPARAM, LPARAM)>> commandLUT{};

};

