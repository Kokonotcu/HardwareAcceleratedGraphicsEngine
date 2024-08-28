#define WHEEL_DELTA 120

#include "Mouse.h"

bool Mouse::KeyIsPressed(Event::Type _type) const noexcept
{
    return mouseBuffer.front().GetType() == _type;
}

Mouse::Event Mouse::ReadEvent() noexcept
{   
    if (mouseBuffer.size() > 0u) 
    {
        Mouse::Event e = mouseBuffer.front();
        mouseBuffer.pop();
        return e;
    }
    else 
    {
        return Mouse::Event();
    }
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
    x = (int)newX;
    y = (int)newY;

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
    middleIsPressed = true;

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
    middleIsPressed = false;

    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::MRelease, *this));
    TrimBuffer();
}

void Mouse::OnMouseEnter()noexcept 
{
    isInWindow = true;
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
    TrimBuffer();
}

void Mouse::OnMouseLeave()noexcept
{
    isInWindow = false;
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
    TrimBuffer();
}

void Mouse::OnWheelUp() noexcept
{
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
    TrimBuffer();
}

void Mouse::OnWheelDown() noexcept
{
    mouseBuffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
    TrimBuffer();
}

void Mouse::OnWheelDelta(int delta) noexcept 
{
    wheelDeltaCarry += delta;

    while (wheelDeltaCarry >= WHEEL_DELTA) 
    {
        wheelDeltaCarry -= WHEEL_DELTA;
        OnWheelUp();
    }
    while (wheelDeltaCarry <= -WHEEL_DELTA)
    {
        wheelDeltaCarry += WHEEL_DELTA;
        OnWheelDown();
    }
}

void Mouse::TrimBuffer() noexcept
{
    while (mouseBuffer.size() > bufferSize)
    {
        mouseBuffer.pop();
    }
}
