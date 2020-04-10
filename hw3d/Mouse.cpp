#include "Window.h"
#include "ChiliWin.h"

//	public access funcs
std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x, y };
}
int Mouse::GetPosX() const noexcept
{
	return x;
}
int Mouse::GetPosY() const noexcept
{
	return y;
}
bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}
bool Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}
bool Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}
int Mouse::GetWheelDeltaCarry() const noexcept
{
	return wheelDeltaCarry;
}

Mouse::Event Mouse::Read() noexcept
{
	if( buffer.size() > 0u )
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

//	member funcs
void Mouse::OnMouseMove( int newx, int newy ) noexcept
{
	x = newx;
	y = newy;
	buffer.push( Mouse::Event( Mouse::Event::Type::Move, *this ) );
	TrimBuffer();
}
void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push( Mouse::Event( Mouse::Event::Type::Leave, *this ) );
	TrimBuffer();
}
void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push( Mouse::Event( Mouse::Event::Type::Enter, *this ) );
	TrimBuffer();
}
void Mouse::OnLeftPressed( int newx, int newy ) noexcept
{
	leftIsPressed = true;

	buffer.push( Mouse::Event( Mouse::Event::Type::LPress, *this ) );
	TrimBuffer();
}
void Mouse::OnLeftReleased( int newx, int newy ) noexcept
{
	leftIsPressed = false;

	buffer.push( Mouse::Event( Mouse::Event::Type::LRelease, *this ) );
	TrimBuffer();
}
void Mouse::OnRightPressed( int newx, int newy ) noexcept
{
	rightIsPressed = true;

	buffer.push( Mouse::Event( Mouse::Event::Type::RPress, *this ) );
	TrimBuffer();
}
void Mouse::OnRightReleased( int newx, int newy ) noexcept
{
	leftIsPressed = false;

	buffer.push( Mouse::Event( Mouse::Event::Type::RPress, *this ) );
	TrimBuffer();
}
void Mouse::OnWheelUp( int newx, int newy ) noexcept
{
	buffer.push( Mouse::Event( Mouse::Event::Type::WheelUp, *this ) );
	TrimBuffer();
}
void Mouse::OnWheelDown( int newx, int newy ) noexcept
{
	buffer.push( Mouse::Event( Mouse::Event::Type::WheelDown, *this ) );
	TrimBuffer();
}
void Mouse::TrimBuffer() noexcept
{
	while( buffer.size() > bufferSize )
	{
		buffer.pop();
	}
}
void Mouse::OnWheelDelta( int newx, int newy, int delta ) noexcept
{
	wheelDeltaCarry += delta;
	//	generate events for every 120
	while( wheelDeltaCarry >= WHEEL_DELTA )
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp( newx, newy );
	}
	while( wheelDeltaCarry <= -WHEEL_DELTA )
	{
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown( x, y );
	}
}
