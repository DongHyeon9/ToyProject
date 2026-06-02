#include "WinApp.h"

int APIENTRY MAIN(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    WindowDesc desc{};
    desc.instance = hInstance;
    desc.cmdShow = nCmdShow;

    if(!WinApp::GetInstance().Init(desc))
    {
        LOG("Initialize Fail");
        std::wcout << L"Please Press Any Key";
        while (true)
            if (_kbhit()) break;

        return -1;
    }

    WinApp::GetInstance().Run();

    WinApp::GetInstance().Terminate();

    return 0;
}