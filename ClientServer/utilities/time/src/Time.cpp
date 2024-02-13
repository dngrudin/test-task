
#include <stdlib.h>
#include <sys/time.h>

#include "Time.hpp"

#define MILLISECONDS_IN_SECOND 1000
#define MICROSECONDS_IN_MILLISECOND 1000

Milliseconds getCurrentTime() {
  timeval time;
  gettimeofday(&time, NULL);
  return static_cast<Milliseconds>(time.tv_sec) * MILLISECONDS_IN_SECOND +
         time.tv_usec / MICROSECONDS_IN_MILLISECOND;
}
