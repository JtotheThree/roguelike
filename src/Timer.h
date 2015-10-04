#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <set>

using std::chrono::milliseconds;

class Timer {
public:
	Timer( milliseconds expiration_time, bool start_active = false );
	Timer( const Timer& ) = delete;

	Timer& operator = ( const Timer & ) = delete;
	~Timer();

	void Reset();

	bool IsActive() const;
	bool IsExpired() const;

	milliseconds CurrentTime() const;

	static void UpdateAll( milliseconds elapsed_time );
private:
	void Update( milliseconds elapsed_time );
	
	milliseconds 				current_time;
	const milliseconds 			expiration_time;

	static std::set <Timer *> 	timers;
};

#endif //TIMER_H
