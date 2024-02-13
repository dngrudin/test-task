
#include "Mutex.hpp"

Mutex::Mutex() { pthread_mutex_init(&mMutex, NULL); }

Mutex::~Mutex() {
  pthread_mutex_unlock(&mMutex);
  pthread_mutex_destroy(&mMutex);
}

void Mutex::lock() { pthread_mutex_lock(&mMutex); }

void Mutex::release() { pthread_mutex_unlock(&mMutex); }

MutexLocker::MutexLocker(Mutex &mutex) : mMutex(mutex) { lock(); }

MutexLocker::~MutexLocker() { release(); }

void MutexLocker::lock() { mMutex.lock(); }

void MutexLocker::release() { mMutex.release(); }
