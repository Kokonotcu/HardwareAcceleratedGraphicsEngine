#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
    return keystates[keycode];
}

Keyboard::Event Keyboard::ReadKey() noexcept 
{
	if (keybuffer.size()> 0u)
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

void Keyboard::ClearKey() noexcept
{
	keybuffer = std::queue<Event>();
}

char Keyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void Keyboard::ClearChar() noexcept
{
	charbuffer = std::queue<char>();
}

void Keyboard::Clear() noexcept
{
	ClearKey();
	ClearChar();
}

void Keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keycode, long long lParam) noexcept
{
	//If autorepeat is enabled and The repeat bit is true
	if ( autorepeatEnabled && (0b1 & (lParam >> 30)))
	{
		OnKeyHolding(keycode);
	}
	else 
	{
		keystates[keycode] = true;
		keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
		TrimBuffer(keybuffer);
	}
}
void Keyboard::OnKeyHolding(unsigned char keycode) noexcept
{
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Holding, keycode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size()>bufferSize)
	{
		buffer.pop();
	}
}