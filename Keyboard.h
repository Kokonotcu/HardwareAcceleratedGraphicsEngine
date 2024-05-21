#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	struct Event 
	{
	public:
		enum class Type 
		{
			Press,
			Holding,
			Release,
			Invalid,
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			code(0u)
		{}
		Event(Type _type , unsigned char _code) noexcept
			:
			type(_type),
			code(_code)
		{}
		bool IsPress() const noexcept 
		{
			return type == Type::Press;
		}
		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}
		bool IsHold() const noexcept
		{
			return type == Type::Holding;
		}
		bool IsValid() 
		{
			return type != Type::Invalid;
		}
		unsigned char GetCode() 
		{
			return code;
		}
	};
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator =(const Keyboard&) = delete;
	
	//Manage key events
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void ClearKey() noexcept;

	//Manage Char events
	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void ClearChar() noexcept;
	void Clear() noexcept;

	//Autorepeat control
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;
private:
	void OnKeyPressed(unsigned char keycode,long long  lParam) noexcept;
	void OnKeyHolding(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};
