#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	struct Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			MPress,
			MRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};
	private:
		Type type;
		float x;
		float y;
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			x(0),
			y(0)
		{}
		Event(Type _type, const Mouse& _parent) noexcept
			:
			type(_type),
			x(_parent.x),
			y(_parent.y)
		{}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		std::pair<float, float> GetPos() const noexcept
		{
			return { x,y };
		}
		bool LIsPressed() const noexcept
		{
			return type==Type::LPress;
		}
		bool RIsPressed() const noexcept
		{
			return type == Type::RPress;
		}
		bool MIsPressed() const noexcept
		{
			return type == Type::MPress;
		}
		Type GetType() const noexcept
		{
			return type;
		}
	};
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator =(const Mouse&) = delete;

	//Manage mouse events
	bool KeyIsPressed(Event::Type _type) const noexcept;
	Event ReadEvent() noexcept;
	std::pair<float, float>GetPos()const noexcept;
	bool IsInWindow() const noexcept 
	{
		return isInWindow; 
	}
	void Clear() noexcept;
	bool IsEmpty() const noexcept 
	{
		return mouseBuffer.empty();
	}


private:
	void OnMouseMove(float newX, float newY) noexcept;
	void OnLeftPressed() noexcept;
	void OnRightPressed() noexcept;
	void OnMiddlePressed() noexcept;
	void OnLeftReleased() noexcept;
	void OnRightReleased() noexcept;
	void OnMiddleReleased() noexcept;
	void OnMouseEnter() noexcept;
	void OnMouseLeave() noexcept;

	void WheelUp() noexcept;
	void WheelDown() noexcept;

	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool middleIsPressed = false;
	bool isInWindow = false; 
	int x;
	int y;
	std::queue<Event> mouseBuffer;
};

