#include <DX3D/Window/Window.h>
#include <Windows.h>
#include <stdexcept>

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0; // Indicate the message was handled
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}
dx3d::Window::Window(const WindowDesc& desc): Base(desc.base), m_size(desc.size)
{
	std::clog << "WINDOW CONSTRUCTOR" << "\n";
	auto registerWindowClassFunction = []()
		{
			WNDCLASSEX wc{};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = L"DX3DWindow";
			wc.lpfnWndProc = &WindowProcedure;
			return RegisterClassEx(&wc);
		};

	static const auto windowClassId = std::invoke(registerWindowClassFunction);

	//let's handle the exception that can be thrown by the RegisterClass
	if (!windowClassId)
	{
		DX3DLogErrorAndThrow("RegisterClassEx failed.");
	}

	RECT rc{ 0, 0, m_size.width, m_size.height };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	//this is the game window
	m_handle = CreateWindowEx(NULL, MAKEINTATOM(windowClassId), L"Pradeep | C++ 3d Game",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, NULL, NULL);

	//let's handle the exception that can be thrown by the CreateWindowEx
	if (!m_handle)
	{
		DX3DLogErrorAndThrow("CreateWindowEx failed.");
	}

	//it's time to show the window
	ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);
}

dx3d::Window::~Window()
{
	//destroy the window
	std::clog << "window destructor" << "\n";
	DestroyWindow(static_cast<HWND>(m_handle));
}