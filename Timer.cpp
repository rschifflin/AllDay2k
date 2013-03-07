#include "Timer.hpp"   //Implementation of this header
#include "SDL/SDL.h" //Used for getTicks()

	void Timer::start()
{
	if (!m_isLive)
	{
		m_startTicks = SDL_GetTicks();
		m_isLive = true;
	}
}

	void Timer::stop()
{
	if (m_isLive)
	{
		m_ticks += SDL_GetTicks() - m_startTicks;
		m_isLive = false;
	}
}

	void Timer::reset()
{
	m_ticks = 0;
	m_isLive = false;
}

	uint32_t Timer::getTicks()
{
	if (m_isLive)
		return m_ticks + (SDL_GetTicks() - m_startTicks);
	else
		return m_ticks;
}
