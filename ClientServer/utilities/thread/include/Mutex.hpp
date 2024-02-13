#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

class Mutex {
  friend class ConditionVariable;

public:
  Mutex();
  ~Mutex();

  void lock();
  void release();

private:
  pthread_mutex_t mMutex;
};

class MutexLocker {
public:
  MutexLocker(Mutex &mutex);
  ~MutexLocker();

  void lock();
  void release();

private:
  Mutex &mMutex;
};

#endif // MUTEX_HPP
