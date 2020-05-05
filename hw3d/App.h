#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "Model.h"
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
private:
	ImguiManager imgui;
	Window wnd;
	ChiliTimer timer;
	bool show_demo_window = true;
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light;
	Model nano{ wnd.Gfx(),"Models\\nanosuit.obj" };
};