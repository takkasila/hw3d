#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "TestPlane.h"
#include "Mesh.h"
#include <set>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
private:
	bool showDemoWindow = false;
	int x = 0, y = 0;
	ImguiManager imgui;
	Window wnd;
	ChiliTimer timer;
	bool show_demo_window = true;
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light;
	Model gobber{ wnd.Gfx(),"Models\\gobber\\GoblinX.obj", 6.0f };
	Model wall{ wnd.Gfx(),"Models\\brick_wall\\brick_wall.obj", 6.0f };
	TestPlane tp{ wnd.Gfx(), 6.0 };
	Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj", 2.0f };
};