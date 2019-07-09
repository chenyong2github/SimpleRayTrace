#include "pch.h"
#include "SimpleRayTrace.h"

#include <chrono>


SimpleRayTrace::SimpleRayTrace()
{
}


SimpleRayTrace::~SimpleRayTrace()
{
}

void SimpleRayTrace::HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		ValidateRect(window, NULL);
		break;
	default:
		break;
	}
}

// MS-Windows event handling function:
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	SimpleRayTrace* srt = reinterpret_cast<SimpleRayTrace *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	srt->HandleMessages(hWnd, uMsg, wParam, lParam);

	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

void SimpleRayTrace::InitWindow(int32_t default_width, int32_t default_height)
{
	width = default_width;
	height = default_height;

	WNDCLASSEX win_class;
	assert(width > 0);
	assert(height > 0);

	connection = GetModuleHandle(NULL);
	sprintf_s(name, "SimpleRayTrace");

	// Initialize the window class structure:
	win_class.cbSize = sizeof(WNDCLASSEX);
	win_class.style = CS_HREDRAW | CS_VREDRAW;
	win_class.lpfnWndProc = WndProc;
	win_class.cbClsExtra = 0;
	win_class.cbWndExtra = 0;
	win_class.hInstance = connection;  // hInstance
	win_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	win_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	win_class.lpszMenuName = NULL;
	win_class.lpszClassName = name;
	win_class.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	// Register window class:
	if (!RegisterClassEx(&win_class)) {
		// It didn't work, so try to give a useful error:
		printf("Unexpected error trying to start the application!\n");
		fflush(stdout);
		exit(1);
	}
	// Create window with the registered class:
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	window = CreateWindowEx(0,
		name,             // class name
		name,             // app name
		WS_OVERLAPPEDWINDOW |  // window style
		WS_VISIBLE | WS_SYSMENU,
		100, 100,            // x/y coords
		wr.right - wr.left,  // width
		wr.bottom - wr.top,  // height
		NULL,                // handle to parent
		NULL,                // handle to menu
		connection,     // hInstance
		NULL);               // no extra parameters
	if (!window) {
		// It didn't work, so try to give a useful error:
		printf("Cannot create a window in which to draw!\n");
		fflush(stdout);
		exit(1);
	}

	SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);
}


void SimpleRayTrace::RenderLoop()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!IsIconic(window)) {
			RenderFrame();
		}
	}
}

auto _lastTime = std::chrono::high_resolution_clock::now();
void SimpleRayTrace::RenderFrame()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto tDiff = std::chrono::duration<double, std::milli>(time - _lastTime).count();
	float deltaTime = (float)tDiff / 1000.0f;
	_lastTime = time;

	//	std::cout << deltaTime << std::endl;

	Update(deltaTime);

	Render();
}