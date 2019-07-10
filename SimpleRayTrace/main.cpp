// SimpleRayTrace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Windows.h"
#include <iostream>
#include <chrono>

#include "platform.h"
#include "scene.h"
#include "camera.h"

static HWND window;

auto _lastTime = std::chrono::high_resolution_clock::now();
void RenderFrame()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto tDiff = std::chrono::duration<double, std::milli>(time - _lastTime).count();
	float deltaTime = (float)tDiff / 1000.0f;
	_lastTime = time;

	//	std::cout << deltaTime << std::endl;
}

void Loop()
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

int main()
{
    std::cout << "Hello World!\n"; 
	window = InitWindow(800, 600);

	Loop();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
