
#ifndef TIME_HPP
#define TIME_HPP

#include <stdint.h>
#include <sys/time.h>

typedef int64_t Milliseconds;

Milliseconds getCurrentTime();

#endif // TIME_HPP