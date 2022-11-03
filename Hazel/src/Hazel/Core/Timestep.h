#pragma once

namespace Hazel
{
	class Timestep
	{
	private:
		float m_time;

	public:
		Timestep(float time = 0.0f)
			: m_time(time)
		{

		}

		float seconds() const { return m_time; }
		float milliseconds() const { return m_time * 1000.0f; }

		operator float() const { return m_time; }
	};
}
