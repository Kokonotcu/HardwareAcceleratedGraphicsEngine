#include "Time.h"

namespace Time 
{
	namespace
	{
		float Delta = 0.0f;
		auto last = std::chrono::steady_clock::now();
	}

	void Time::CalculateDelta()
	{
		const auto old = last;
		last = std::chrono::steady_clock::now();
		const std::chrono::duration<float> t = last - old;
		Delta = t.count();
	}
	const float delta() 
	{
		return Delta;
	}
}