#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjScheduler_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjScheduler_HPP_

#include "framework/task/1_0/Task.hpp"
#include "framework/active_object/1_0/ActivationQueue.hpp"

namespace ExActiveObject
{

class ActObjScheduler : public Task_1_0::Task
{
  public:
    ActObjScheduler();
    virtual ~ActObjScheduler();
    int svc() override;
    int enqueue( ActiveObject_1_0::MethodRequest *request );

  private:
    ActiveObject_1_0::ActivationQueue mActivationQueue;
};
} //namespace ExActiveObject

#endif /* APPLICATIONS_EXAMPLE_ActObjScheduler_HPP_ */