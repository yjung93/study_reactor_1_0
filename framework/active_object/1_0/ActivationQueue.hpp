#ifndef FRAMEWORK_ACTIVE_OBJECT_1_0_ACTIVATION_QUEUE_HPP_
#define FRAMEWORK_ACTIVE_OBJECT_1_0_ACTIVATION_QUEUE_HPP_

#include <vector>
#include <mutex>
#include <condition_variable>

#include "MethodRequest.hpp"

using namespace std;

namespace ActiveObject_1_0
{

class ActivationQueue
{
  enum State{
    STATE_ACTIVE,
    STATE_SHUTDOWN
  };
  public:
    ActivationQueue();
    virtual ~ActivationQueue();

    MethodRequest *dequeue();
    int enqueue( MethodRequest *newMethodRequest );

    void exit();

  private:
    vector<MethodRequest*> mMethodRequestQueue;
    mutex mQueueMutex;
    condition_variable mQueueCondition;

    State mState;

};

} //namespace ActiveObject_1_0
#endif // FRAMEWORK_ACTIVE_OBJECT_1_0_ACTIVATION_QUEUE_HPP_