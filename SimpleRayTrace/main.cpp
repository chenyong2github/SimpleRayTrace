// SimpleRayTrace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Windows.h"
#include <iostream>
#include <chrono>

#include "platform.h"
#include "scene.h"
#include "camera.h"
#include "random_sort.h"

static Camera* BuildCamera(RectSize windowSize);
static void PopulateCoordinateArray(OrderedPair array[], RectSize windowSize);
static void BuildScene();
void RenderFrame();

int main()
{
    std::cout << "Hello World!\n";

	RectSize windowSize = { 800, 600 };

	InitWindow(windowSize.width, windowSize.height);

	// Set up the pixel coordinate array and scramble it
	int totalPixelCount = windowSize.width * windowSize.height;
	OrderedPair* coordinateArray = new OrderedPair[totalPixelCount];

	PopulateCoordinateArray(coordinateArray, windowSize);

	// Set up the scene and camera
	Camera* cam = BuildCamera(windowSize);

	BuildScene();

	for (int index = 0; index < totalPixelCount; index++) {
		OrderedPair pixelCoord = coordinateArray[index];

		int i = pixelCoord.i;
		int j = pixelCoord.j;

		Color pixelColor = CameraSamplePixel(cam, i, j, windowSize);
		SetColor(i, windowSize.height - j, pixelColor); // invert y-axis
	}

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

static Camera* BuildCamera(RectSize windowSize)
{
	Vec3 camPos = { 0, 0.75f, 0 };
	Vec3 upDir = { 0, 1, 0 };
	Vec3 viewDir = { 0, -0.25f, -1 };

	float aspect = windowSize.width / (float)windowSize.height;
	RectSize imagePlaneSize = { 2 * aspect, 2 };

	Color background = { 0, 0, 0, 1 };

	//    Camera* cam = CameraCreateOrthographic(camPos, upDir, viewDir,
	//                                           imagePlaneSize, background);
	Camera* cam = CameraCreatePerspective(camPos, upDir, viewDir,
		imagePlaneSize, background,
		/* focal length = */ 1.73f);
	return cam;
}

static void BuildScene()
{
	Vec3 lightDirection = { -1, 0.75f, 0.5f };
	SceneInit(lightDirection, /* ambient light intensity = */ 0.2f);

	Color floorColor = { 0.4f, 0.4f, 0.33f, 1 };
	Color darkGray = { 0.2f, 0.2f, 0.2f, 1 };
	Color gray = { 0.6f, 0.6f, 0.6f, 1 };
	Color red = { 0.71f, 0.25f, 0.25f, 1 };
	Color blue = { 0.31f, 0.52f, 0.85f, 1 };
	Color green = { 0.33f, 0.71f, 0.31f, 1 };

	// Create a floor from two tris
	Vec3 a = { -5, 0, 0 };
	Vec3 b = { 5, 0, 0 };
	Vec3 c = { -5, 0, -10 };
	Triangle* left = TriangleCreate(a, b, c, floorColor, gray, 10, darkGray);
	SceneAddTriangle(left);

	Vec3 d = { -5, 0, -10 };
	Vec3 e = { 5, 0, 0 };
	Vec3 f = { 5, 0, -10 };
	Triangle* right = TriangleCreate(d, e, f, floorColor, gray, 10, darkGray);
	SceneAddTriangle(right);

	// Add colored spheres
	Vec3 blueSphereCenter = { 0.60f, 0.5f, -3.10 };
	Sphere* blueSphere = SphereCreate(blueSphereCenter, 0.5f, blue,
		darkGray, 10, BLACK_COLOR);
	SceneAddSphere(blueSphere);

	Vec3 greenSphereCenter = { -0.65f, 0.5f, -2.75f };
	Sphere* greenSphere = SphereCreate(greenSphereCenter, 0.5f, green,
		gray, 100, BLACK_COLOR);
	SceneAddSphere(greenSphere);
}

static void PopulateCoordinateArray(OrderedPair array[], RectSize windowSize)
{
	for (int i = 0; i < windowSize.width; i++) {
		for (int j = 0; j < windowSize.height; j++) {
			int index = j + i * windowSize.height;
			array[index].i = i;
			array[index].j = j;
		}
	}

	int totalPixelCount = windowSize.width * windowSize.height;
	RandomSort(array, totalPixelCount);
}


auto _lastTime = std::chrono::high_resolution_clock::now();
void RenderFrame()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto tDiff = std::chrono::duration<double, std::milli>(time - _lastTime).count();
	float deltaTime = (float)tDiff / 1000.0f;
	_lastTime = time;
}