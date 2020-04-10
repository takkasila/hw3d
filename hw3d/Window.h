#pragma once
#include "ChiliWin.h"
#include "ChiliException.h"
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

#include <optional>
#include <memory>

class Window
{
public:
	//	exception handler
	class Exception : public ChiliException
	{
	public:
		//	constructor 
		Exception(int line, const char* file, HRESULT hr ) noexcept;
		//	override access funcs
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		//	new hifty nifty functions
		static std::string TranslateErrorCode( HRESULT hr ) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

private:
	//	singleton manages registration/cleanup of window class
	class WindowClass
	{
		//	public interface
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		//	private constructor/destructor
		WindowClass() noexcept;
		~WindowClass();
		WindowClass( const WindowClass& ) = delete;
		WindowClass& operator=( const WindowClass& ) = delete;
		//	private properties
		static constexpr const char* wndClassName = "Chili Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	//	constructor/destructors
	Window( int width, int height, const char* name );
	~Window();
	Window( const Window& ) = delete;
	Window& operator=( const Window& ) = delete;

public:
	//	public access funcs
	void SetTitle( const std::string& title );
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();
	
private:
	//	member functions
	static LRESULT CALLBACK HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) noexcept;
	static LRESULT CALLBACK HandleMsgThunk( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) noexcept;
	LRESULT HandleMsg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) noexcept;
public:
	//	public member attributes
	Keyboard kbd;
	Mouse mouse;

private:
	//	member attributes
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

//	error exception helper macro
#define CHWND_EXCEPT( hr ) Window::Exception( __LINE__, __FILE__, hr )
#define CHWND_LAST_EXCEPT() Window::Exception( __LINE__, __FILE__, GetLastError() )