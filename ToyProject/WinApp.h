#pragma once
#include "EngineCore.h"

class WinApp : public ISingleton<WinApp>
{
public:
	bool Init(const WindowDesc& Desc);

	void Run();
	void Terminate();

	Vector2 GetWindowSize() const { return desc.size; }
	HWND GetWindowHandle() const { return desc.wnd; }
	HINSTANCE GetInst() const { return desc.instance; }
	void SetWindowSize(const Vector2& newSize) { desc.size = newSize; }

private:
	void Update();
	void Render();
	bool RegisterWindowClass();
	bool InitWindow();
	bool InitManager();

private:
	WindowDesc desc{};
	
};

