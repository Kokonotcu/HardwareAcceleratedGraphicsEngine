#include "Mouse.h"

bool Mouse::KeyIsPressed(Event::Type _type) const noexcept
{
    return mouseBuffer.front().GetType() == _type;
}

Mouse::Event Mouse::ReadEvent() noexcept
{
    return mouseBuffer.front();
}

std::pair<float, float> Mouse::GetPos() const noexcept
{
    return mouseBuffer.front().GetPos();
}

void Mouse::Clear() noexcept
{
    mouseBuffer = std::queue<Event>();
}

void Mouse::OnMouseMove(float newX, float newY) noexcept
{
    x = newX;
    y = newY;

    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::Move,*this));
    TrimBuffer();
}

void Mouse::OnLeftPressed() noexcept
{
    leftIsPressed = true;

    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
    TrimBuffer();
}

void Mouse::OnRightPressed() noexcept
{
    rightIsPressed = true;

    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
    TrimBuffer();
}

void Mouse::OnMiddlePressed() noexcept
{
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::MPress, *this));
    TrimBuffer();
}

void Mouse::OnLeftReleased() noexcept
{
    leftIsPressed = false;

    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
    TrimBuffer();
}

void Mouse::OnRightReleased() noexcept
{
    rightIsPressed = false;

    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
    TrimBuffer();
}

void Mouse::OnMiddleReleased() noexcept
{ 
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::MRelease, *this));
    TrimBuffer();
}

void Mouse::WheelUp() noexcept
{
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
    TrimBuffer();
}

void Mouse::WheelDown() noexcept
{
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
    TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
    while (mouseBuffer.size() > bufferSize)
    {
        mouseBuffer.pop();
    }
}
