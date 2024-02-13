
#include "ConditionVariable.hpp"

ConditionVariable::ConditionVariable() { pthread_cond_init(&mCV, NULL); }

ConditionVariable::~ConditionVariable() { pthread_cond_destroy(&mCV); }

void ConditionVariable::notify() { pthread_cond_broadcast(&mCV); }
