
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "Thread.hpp"

Thread::Thread() : mRunning(false), mStop(true) {}

Thread::~Thread() { stop(); }

void Thread::usleep(unsigned int us) { ::usleep(us); }

void Thread::yield() { sched_yield(); }

void Thread::start() {
  if (mRunning) {
    return;
  }

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  if (pthread_create(&mThread, &attr, Thread::woker, this) != 0) {
    mRunning = false;
  } else {
    mRunning = true;
  }
  pthread_attr_destroy(&attr);
}

void Thread::stop() {
  if (!mRunning)
    return;

  while (!mStop) {
    ::usleep(10);
  }

  if (pthread_join(mThread, NULL) != 0) {
    mRunning = true;
  } else {
    mRunning = false;
  }
}

void *Thread::woker(void *data) {
  Thread *thread = (Thread *)data;

  thread->mStop = false;
  thread->task();
  thread->mStop = true;

  return NULL;
}
