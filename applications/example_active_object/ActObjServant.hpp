#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServant_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServant_HPP_

#include "framework/task/1_0/Task.hpp"

using namespace std;
namespace ExActiveObject
{
class ActObjServant : public Task_1_0::Task
{
  public:
    ActObjServant();
    virtual ~ActObjServant();
    int svc() override;
    int open( void *args = 0 ) override;

  private:
    void processMessage( const std::string &message );
};

} //namespace ExActiveObject

#endif /* APPLICATIONS_EXAMPLE_ActObjServant_HPP_ */
