#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid,
		};

	private:
		//	member
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		int x;
		int y;

	public:
		//	set default constructor to construct invalid
		Event() noexcept
			:	type( Type::Invalid ),
				leftIsPressed( false ),
				rightIsPressed( false ),
				x( 0 ),
				y( 0 )
		{
		}

		Event( Type type, const Mouse& parent ) noexcept
			:	type(type),
				leftIsPressed( parent.leftIsPressed ),
				rightIsPressed( parent.rightIsPressed ),
				x( parent.x ),
				y( parent.y )
		{
		}

		//	public access funcs
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		Type GetType() const noexcept
		{
			return type;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return { x, y };
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return leftIsPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return rightIsPressed;
		}
	};

public:
	//	use default constructor
	Mouse() = default;

	//	delete unused operators
	Mouse( const Mouse& ) = delete;
	Mouse& operator=( const Mouse& ) = delete;

	//	public access funcs
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool IsInWindow() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	int GetWheelDeltaCarry() const noexcept;
	Mouse::Event Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Flush() noexcept;

private:
	//	member funcs
	void OnMouseMove( int newx, int newy ) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnLeftPressed( int newx, int newy ) noexcept;
	void OnLeftReleased( int newx, int newy ) noexcept;
	void OnRightPressed( int newx, int newy ) noexcept;
	void OnRightReleased( int newx, int newy ) noexcept;
	void OnWheelUp( int newx, int newy ) noexcept;
	void OnWheelDown( int newx, int newy ) noexcept;
	void TrimBuffer() noexcept;
	void OnWheelDelta( int newx, int newy, int delta ) noexcept;

private:
	//	member
	static constexpr unsigned int bufferSize = 16u;
	int x;
	int y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
	int wheelDeltaCarry = 0;
	std::queue<Mouse::Event> buffer;
		
};
