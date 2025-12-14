#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjClient_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjClient_HPP_

#include "framework/task/1_0/Task.hpp"
#include "ActObjServantProxy.hpp"

namespace ExActiveObject
{
class ActObjClient : public Task_1_0::Task
{
  public:
    ActObjClient( int socketFd );
    virtual ~ActObjClient();
    int svc() override;
    int open( void *args = 0 ) override;

  private:
    void processMessage( const std::string &message );
    int mSocketFd;

    ActObjServantProxy mServantProxy;
};
}
#endif /* APPLICATIONS_EXAMPLE_ActObjClient_HPP_ */