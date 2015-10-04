#include "Timer.h"

std::set <Timer *> Timer::timers;

Timer::Timer( milliseconds expiration_time_, bool start_active ) :
	current_time{ start_active ? 0 : expiration_time_.count() + 1},
	expiration_time{ expiration_time_ }
{
	timers.insert( this );
}

Timer::~Timer() {
	timers.erase( this );
}

void Timer::Reset() {
	current_time = current_time.zero();
}

bool Timer::IsActive() const {
	return current_time < expiration_time;
}

bool Timer::IsExpired() const {
	return IsActive();
}

milliseconds Timer::CurrentTime() const {
	return current_time;
}

void Timer::UpdateAll( milliseconds elapsed_time ) {
	for ( auto timer : timers ) {
		timer->Update( elapsed_time );
	}
}

void Timer::Update( milliseconds elapsed_time ) {
	if ( IsActive() ) {
		current_time += elapsed_time;
	}
}
