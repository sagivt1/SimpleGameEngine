#include "WindowsWindow.h"

Engine::WindowsWindow::WindowsWindow()
{
    m_hInstance = GetModuleHandle(nullptr);

    // === Be DPI aware ===
   
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// === Register window class ===

	WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = &WindowsWindow::WindowProc_Setup;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"GameEngienWidnow";
    wcex.hIconSm = nullptr;

    m_windowClass = RegisterClassExW(&wcex);

    // === Create the window ===
    m_wnd = CreateWindowExW(
        WS_EX_OVERLAPPEDWINDOW,
        (LPCWSTR)m_windowClass,
        L"Game",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        10, 10,
        m_width,
        m_height,
        nullptr,
        nullptr,
        m_hInstance,
        this
    );
}

Engine::WindowsWindow::~WindowsWindow()
{
    DestroyWindow(m_wnd);
    UnregisterClassW((LPCWSTR)m_windowClass, m_hInstance);
}

bool Engine::WindowsWindow::CloseRequsted()
{
    bool closeRquest = m_closeRquest;
    m_closeRquest = false;
    return closeRquest;
}

void Engine::WindowsWindow::Update()
{
    MSG msg{};
    while (PeekMessageW(&msg, m_wnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

size_t Engine::WindowsWindow::GetWidth()
{
	return m_width;
}

size_t Engine::WindowsWindow::GetHeight()
{
	return m_height;
}

LRESULT Engine::WindowsWindow::WindowProc_Setup(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (msg == WM_NCCREATE)
    {
        auto* createStruct = (CREATESTRUCT*)lparam;
        SetWindowLongPtrW(wnd, GWLP_USERDATA, (LONG_PTR)createStruct->lpCreateParams);
        SetWindowLongPtrW(wnd, GWLP_WNDPROC, (LONG_PTR)&WindowsWindow::WindowProc_Redirect);
        return WindowProc_Redirect(wnd, msg, wparam, lparam);
    }
    return DefWindowProcW(wnd, msg, wparam, lparam);
}

LRESULT Engine::WindowsWindow::WindowProc_Redirect(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    auto* window = (WindowsWindow*)GetWindowLongPtrW(wnd, GWLP_USERDATA);
    return window->WindowProc(wnd, msg, wparam, lparam);
}

LRESULT Engine::WindowsWindow::WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_CLOSE:
            m_closeRquest = true;
            return 0;
        case WM_SIZE:
            if(LOWORD(lparam) >= 64 && HIWORD(lparam) >= 64)
            { 
                m_width = LOWORD(lparam);
                m_height = HIWORD(lparam);
            }
            break;
    }
    return DefWindowProcW(wnd, msg, wparam, lparam);
}

