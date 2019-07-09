#pragma once

#include <cstdlib>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "Windows.h"


class SimpleRayTrace
{
public:
	SimpleRayTrace();
	~SimpleRayTrace();
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
	virtual void Destroy() {};
	void InitWindow(int32_t default_width, int32_t default_height);
	void HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// Start the main render loop
	void RenderLoop();
	// Render one frame of a render loop on platforms that sync rendering
	void RenderFrame();
public:
	#define APP_NAME_STR_LEN 80
	HINSTANCE connection;        // hInstance - Windows Instance
	char name[APP_NAME_STR_LEN]; // Name to put on the window/icon
	HWND window;                 // hWnd - window handle
	int width, height;
};

