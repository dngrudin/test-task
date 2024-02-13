#ifndef COONDITION_VARIABLE_HPP
#define COONDITION_VARIABLE_HPP

#include "Mutex.hpp"

class ConditionVariable {
public:
  ConditionVariable();
  ~ConditionVariable();

  template <typename Predicate> void wait(Mutex &mutex, Predicate predicate);

  void notify();

private:
  pthread_cond_t mCV;
};

template <typename Predicate>
inline void ConditionVariable::wait(Mutex &mutex, Predicate predicate) {
  while (!predicate()) {
    pthread_cond_wait(&mCV, &mutex.mMutex);
  }
}

#endif // COONDITION_VARIABLE_HPP