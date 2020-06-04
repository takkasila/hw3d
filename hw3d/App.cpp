#include "App.h"
#include <memory>
#include <algorithm>
#include "ChiliMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "imgui/imgui.h"
#include "VertexBuffer.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd( 1366, 768, "D3D11 Lmao" ),
	light( wnd.Gfx() )
{
	//wall.SetRootTransform( dx::XMMatrixTranslation( -1.5f, 0.0f, 0.0f ) );
	//tp.SetPos( { 1.5f,0.0f,0.0f } );
	wnd.Gfx().SetProjection( DirectX::XMMatrixPerspectiveLH( 1.0f, (float)wnd.Height() / wnd.Width(), 0.5f, 40.0f ) );
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame( 0.07f, 0.0f, 0.12f );
	wnd.Gfx().SetCamera( cam.GetMatrix() );
	light.Bind( wnd.Gfx(), cam.GetMatrix() );

	//wall.Draw( wnd.Gfx() );
	//tp.Draw( wnd.Gfx() );
	// nano.Draw( wnd.Gfx() );
	gobber.Draw( wnd.Gfx() );
	light.Draw( wnd.Gfx() );

	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		}
	}

	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed( 'W' ))
		{
			cam.Translate( { 0.0f,0.0f,dt } );
		}
		if (wnd.kbd.KeyIsPressed( 'A' ))
		{
			cam.Translate( { -dt,0.0f,0.0f } );
		}
		if (wnd.kbd.KeyIsPressed( 'S' ))
		{
			cam.Translate( { 0.0f,0.0f,-dt } );
		}
		if (wnd.kbd.KeyIsPressed( 'D' ))
		{
			cam.Translate( { dt,0.0f,0.0f } );
		}
		if (wnd.kbd.KeyIsPressed( 'E' ))
		{
			cam.Translate( { 0.0f,dt,0.0f } );
		}
		if (wnd.kbd.KeyIsPressed( 'Q' ))
		{
			cam.Translate( { 0.0f,-dt,0.0f } );
		}
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			cam.Rotate( (float)delta->x, (float)delta->y );
		}
	}

	// imgui windows
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	gobber.ShowWindow( "gobber" );
	//tp.SpawnControlWindow( wnd.Gfx() );
	//ShowImguiDemoWindow();
	//wall.ShowWindow( "Wall" );
	//nano.ShowWindow( "Model 1" );

	// present
	wnd.Gfx().EndFrame();
}

void App::ShowImguiDemoWindow()
{
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow( &showDemoWindow );
	}
}

App::~App()
{}

int App::Go()
{
	while( true )
	{
		// process all messages pending, but to not block for new messages
		if( const auto ecode = Window::ProcessMessages() )
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}
