#ifndef TIMER_H_
#define TIMER_H_


#include <time.h>
#include <cstring>

class Timer
{
public:
	Timer() : m_run(0)
	{
		reset();
	}

	void start()
	{
		clock_gettime(CLOCK_MONOTONIC, &m_t0);
	}

	void stop()
	{
		clock_gettime(CLOCK_MONOTONIC, &m_t1);
	}

	void reset()
	{
		memset(&m_t0, 0, sizeof(struct timespec));
		memset(&m_t1, 0, sizeof(struct timespec));
		m_run = 0;
	}

	void run()
	{
		m_run = 1;
		start();
	}

	float elapsed()
	{
		if (m_run)
			clock_gettime(CLOCK_MONOTONIC, &m_t1);
		return ((m_t1.tv_sec - m_t0.tv_sec) + 1e-9 * (m_t1.tv_nsec - m_t0.tv_nsec));
	}

private:
	struct timespec m_t0;
	struct timespec m_t1;
	int m_run;
};


#endif // TIMER_H_
