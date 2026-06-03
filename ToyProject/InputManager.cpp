#include "InputManager.h"
#include "ObjectManager.h"
#include "GDIManager.h"
#include "WinApp.h"

#define REGIST_MESSAGE(msg, func) messageLUT[msg] = [this](HWND Wnd, WPARAM wParam, LPARAM lParam) { return func(Wnd, wParam, lParam); }
#define REGIST_COMMAND(cmd, func) commandLUT[cmd] = [this](HWND Wnd, WPARAM wParam, LPARAM lParam) { return func(Wnd, wParam, lParam); }
#define REGIST_KEYDOWN(key, func) commandLUT[key] = [this](HWND Wnd, WPARAM wParam, LPARAM lParam) { return func(Wnd, wParam, lParam); }

bool InputManager::Init()
{
	CHECK(RegisterMessage(), "메세지 등록 실패", false);
	CHECK(RegisterCommand(), "커맨드 등록 실패", false);

	LOG("입력 매니저 초기화 성공");
	return true;
}

void InputManager::Terminate()
{

}

bool InputManager::RegisterMessage()
{
	REGIST_MESSAGE(WM_COMMAND, OnCommand);
	REGIST_MESSAGE(WM_KEYDOWN, OnCommand);

	REGIST_MESSAGE(WM_DESTROY, OnDestroy);
	REGIST_MESSAGE(WM_LBUTTONDOWN, OnLButtonDown);
	REGIST_MESSAGE(WM_LBUTTONUP, OnLButtonUp);
	REGIST_MESSAGE(WM_MOUSEMOVE, OnMouseMove);
	REGIST_MESSAGE(WM_SIZE, OnSize);
	
	return true;
}

bool InputManager::RegisterCommand()
{
	REGIST_COMMAND(IDM_EXIT, OnExit);
	REGIST_COMMAND(ID_ALL_DELETE, OnAllDelete);
	REGIST_COMMAND(ID_DOT, OnDot);
	REGIST_COMMAND(ID_LINE, OnLine);
	REGIST_COMMAND(ID_CIRCLE, OnCircle);
	REGIST_COMMAND(ID_TRIANGLE, OnTriangle);
	REGIST_COMMAND(ID_RECT, OnRect);
	REGIST_COMMAND(ID_SELECT_DELETE, OnSelectDelete);

	REGIST_KEYDOWN(VK_ESCAPE, OnEscape);

	return true;
}

LRESULT InputManager::WinProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (messageLUT.contains(Message))
		return messageLUT[Message](Wnd, wParam, lParam);
	return ::DefWindowProc(Wnd, Message, wParam, lParam);
}

LRESULT InputManager::OnCommand(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);

	if(commandLUT.contains(wmId))
		return commandLUT[wmId](Wnd, wParam, lParam);
	return ::DefWindowProc(Wnd, WM_COMMAND, wParam, lParam);
}

LRESULT InputManager::OnDestroy(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);
	return 0;
}

LRESULT InputManager::OnLButtonDown(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	LOG("LButtonDown : (%d, %d)", LOWORD(lParam), HIWORD(lParam));
	ObjectManager::GetInstance().OnButtonDown({ LOWORD(lParam), HIWORD(lParam) });
	return 0;
}

LRESULT InputManager::OnLButtonUp(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	LOG("LButtonUp : (%d, %d)", LOWORD(lParam), HIWORD(lParam));
	ObjectManager::GetInstance().OnButtonUp({ LOWORD(lParam), HIWORD(lParam) });
	return 0;
}

LRESULT InputManager::OnMouseMove(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().OnMouseMove({ LOWORD(lParam), HIWORD(lParam) });
	return 0;
}

LRESULT InputManager::OnSize(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	Vector2 newSize{ static_cast<float>(LOWORD(lParam)), static_cast<float>(HIWORD(lParam)) };
	WinApp::GetInstance().SetWindowSize(newSize);
	return 0;
}

LRESULT InputManager::OnEscape(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().CancelSelect();
	LOG("선택 취소");
	return 0;
}

LRESULT InputManager::OnExit(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);
	return 0;
}

LRESULT InputManager::OnAllDelete(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().AllDelete();
	LOG("전체 삭제");
	return 0;
}

LRESULT InputManager::OnSelectDelete(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().SelectDelete();
	LOG("선택 삭제");
	return 0;
}

LRESULT InputManager::OnDot(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().SetState(EState::Create);
	ObjectManager::GetInstance().SetShapeType(EShapeType::Dot);
	return 0;
}

LRESULT InputManager::OnLine(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().SetState(EState::Create);
	ObjectManager::GetInstance().SetShapeType(EShapeType::Line);
	return 0;
}

LRESULT InputManager::OnCircle(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().SetState(EState::Create);
	ObjectManager::GetInstance().SetShapeType(EShapeType::Circle);
	return 0;
}

LRESULT InputManager::OnTriangle(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().SetState(EState::Create);
	ObjectManager::GetInstance().SetShapeType(EShapeType::Polygon);
	return 0;
}

LRESULT InputManager::OnRect(HWND Wnd, WPARAM wParam, LPARAM lParam)
{
	ObjectManager::GetInstance().SetState(EState::Create);
	ObjectManager::GetInstance().SetShapeType(EShapeType::Rect);
	return 0;
}

#undef REGIST_MESSAGE
#undef REGIST_COMMAND