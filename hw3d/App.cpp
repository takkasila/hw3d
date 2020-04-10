#include "App.h"
#include <sstream>
#include <iomanip>

App::App()
	:	wnd( 800, 600, "The Donkey Fart Box" )
{
}

int App::Go()
{
	while( true )
	{
		//	process all messages pending, but do not block for new messages
		if( const auto ecode = Window::ProcessMessages() )
		{
			//	if return optional has value, means we're quitting so return the exit code
			return *ecode;
		}

		//	execute the game logic
		DoFrame();
	}
}

void App::DoFrame()
{
	const float c = sin( timer.Peek() ) / 2.0 + 0.5f;
	wnd.Gfx().ClearBuffer( c, c, 1.0f );
	wnd.Gfx().EndFrame();
}