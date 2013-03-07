/*	
 *	This header specifies a Timer object. Timers can be started, read
 *	and stopped.
 * */

#ifndef RS_TIMER
#define RS_TIMER

#include <stdint.h> //Used for fixed-width integer

class Timer
{
	
private:
	uint32_t m_ticks; //Number of ticks since timer was last reset
	uint32_t m_startTicks; //Moment when timer was started
	bool	 m_isLive; //Whether or not the timer is active

public:
	Timer() : m_ticks(0), m_startTicks(0), m_isLive(true) {}

	void start();
	void stop();
	void reset();
	uint32_t getTicks();
};

#endif //RS_TIMER
