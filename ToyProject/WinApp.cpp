#include "WinApp.h"

#include "TimerManager.h"
#include "ObjectManager.h"
#include "GDIManager.h"
#include "InputManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool WinApp::Init(const WindowDesc& Desc)
{
	desc = Desc;
	
	//지역 설정
#ifdef UNICODE
	_wsetlocale(LC_ALL, TEXT("korean"));
	LOG("언어설정 : 한국");
#endif

	CHECK(RegisterWindowClass(), "윈도우 클래스 등록 실패", false);
	CHECK(InitWindow(), "윈도우 초기화 실패", false);
	CHECK(InitManager(), "매니저 초기화 실패", false);

	LOG("윈도우 앱 초기화 성공");

	return true;
}

void WinApp::Run()
{
	//프로그램 메인 루프
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		Update();
		Render();
	}
}

void WinApp::Terminate()
{
	TimerManager::GetInstance().Terminate();
	GDIManager::GetInstance().Terminate();
	ObjectManager::GetInstance().Terminate();
	InputManager::GetInstance().Terminate();
}

void WinApp::Update()
{
	double tick = TimerManager::GetInstance().Update();
	::SetWindowText(desc.wnd, (WINDOW_TITLE + TEXT(" - ") + EngineUtil::ToString(static_cast<int32>(1 / tick)) + TEXT(" f/s")).c_str());
}

void WinApp::Render()
{
	RECT rc = GDIManager::GetInstance().RenderBegin(desc.wnd);

	ObjectManager::GetInstance().Render(GDIManager::GetInstance().GetBackBuffer(), rc);

	GDIManager::GetInstance().RenderEnd(desc.wnd);
}

bool WinApp::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = desc.instance;
	wcex.hIcon = ::LoadIcon(desc.instance, MAKEINTRESOURCE(IDI_TOYPROJECT));
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TOYPROJECT);
	wcex.lpszClassName = WINDOW_CLASS.c_str();
	wcex.hIconSm = ::LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return SUCCEEDED(::RegisterClassEx(&wcex));
}

bool WinApp::InitWindow()
{
	desc.wnd = ::CreateWindow(
		WINDOW_CLASS.c_str(),
		WINDOW_TITLE.c_str(),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		static_cast<int>(desc.size.x),
		static_cast<int>(desc.size.y),
		nullptr,
		nullptr,
		desc.instance,
		nullptr);

	if (!desc.wnd)
		return false;

	::ShowWindow(desc.wnd, desc.cmdShow);
	::UpdateWindow(desc.wnd);

	LOG("윈도우 초기화 성공");

	return true;
}

bool WinApp::InitManager()
{
	CHECK(TimerManager::GetInstance().Init(), "타이머 매니저 초기화 실패", false);
	CHECK(GDIManager::GetInstance().Init(), "GDI 매니저 초기화 실패", false);
	CHECK(ObjectManager::GetInstance().Init(), "오브젝트 매니저 초기화 실패", false);
	CHECK(InputManager::GetInstance().Init(), "입력 매니저 초기화 실패", false);

	LOG("매니저 초기화 성공");
	return true;
}

LRESULT CALLBACK WndProc(HWND Wnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	return InputManager::GetInstance().WinProc(Wnd, Message, wParam, lParam);
}