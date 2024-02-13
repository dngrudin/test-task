#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>
#include <sys/types.h>

class Thread {
public:
  Thread();
  virtual ~Thread();

  void start();
  void stop();

  bool isRun() const { return mRunning; }

protected:
  virtual void task() {}

  static void usleep(unsigned int us);
  static void yield();

private:
  static void *woker(void *data);

  bool mRunning;
  bool mStop;

  pthread_t mThread;
};

#endif // THREAD_HPP
