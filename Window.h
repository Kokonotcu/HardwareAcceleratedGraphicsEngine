#pragma once
#include "WindowsMisc.h"
#include "WindException.h"


class Window
{
public:
	class Exception : public WndException
	{
	public:
		Exception(int line, const char*file , HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&)= delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "3D Render Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK HandleMsgStart(HWND hWnd, UINT msg,WPARAM wParam,LPARAM lParam);
	static LRESULT CALLBACK HandleMsgUpdate(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
};

//Easy error macro
#define WND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)
#define WND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError())