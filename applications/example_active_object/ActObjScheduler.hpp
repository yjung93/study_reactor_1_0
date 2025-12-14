#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjScheduler_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjScheduler_HPP_

#include "framework/task/1_0/Task.hpp"

namespace ExActiveObject
{

class ActObjScheduler : public Task_1_0::Task
{
  public:
    ActObjScheduler(  );
    virtual ~ActObjScheduler();
    int svc() override;
    int open( void *args = 0 ) override;

  private:
    void processMessage( const std::string &message );
};
}//namespace ExActiveObject

#endif /* APPLICATIONS_EXAMPLE_ActObjScheduler_HPP_ */