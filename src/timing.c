#include "timing.h"
#include <stdlib.h>

/*
*   struct Timer implementation.
*/

// Get current time with microsecond resolution.
uint64_t get_time_us(void) {
#if defined(__unix__) || defined(__unix) || defined(__APPLE__)&&defined(__MACH__)

	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	return (uint64_t)((t.tv_sec * 1e6) + (t.tv_nsec / 1e3));

#elif defined(_WIN32)

	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
	return (uint64_t)(t.QuadPart * (1e6/f.QuadPart));

#endif
}

struct Timer {
	uint64_t start;
	uint64_t end;
};

struct Timer *create_timer(void) {
	struct Timer *t = malloc(sizeof(struct Timer));
	t->start = 0;
	t->end = 0;
	return t;
}

void destroy_timer(struct Timer *t) {
	free(t);
}

void start_timer(struct Timer *t) {
	t->start = get_time_us();
	t->end = 0;
}

void mark_timer(struct Timer *t) {
	t->end = get_time_us();
}

uint64_t get_elapsed_time(struct Timer *t) {
	return (t->end - t->start);
}

/*
*   Sleep.
*/
void ms_sleep(uint64_t ms_time) {
#if defined(__unix__) || defined(__unix) || defined(__APPLE__)&&defined(__MACH__)

	struct timespec ts;
	ts.tv_sec = ms_time / 1000;
	ts.tv_nsec = (ms_time % 1000) * 100000;
	nanosleep(&ts, NULL);

#elif defined(_WIN32)

	Sleep(ms_time);

#endif
}
