#ifndef APPLICATIONS_EXAMPLE_HalfSynHandler_HPP_
#define APPLICATIONS_EXAMPLE_HalfSynHandler_HPP_

#include "framework/task/1_0/Task.hpp"

class HalfSyncHandler : public Task_1_0::Task
{
  public:
    HalfSyncHandler( int socketFd );
    virtual ~HalfSyncHandler();
    int svc() override;
    int open( void *args = 0 ) override;

  private:
    void processMessage( const std::string &message );
    int mSocketFd;
};

#endif /* APPLICATIONS_EXAMPLE_HalfSynHandler_HPP_ */