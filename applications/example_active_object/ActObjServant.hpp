#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServant_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServant_HPP_

#include "framework/task/1_0/Task.hpp"

using namespace std;
namespace ExActiveObject
{
class ActObjServant
{
  public:
    ActObjServant();
    virtual ~ActObjServant() = default;

    string RequestGetReturnMessage( const string &message );

  private:
};

} //namespace ExActiveObject

#endif /* APPLICATIONS_EXAMPLE_ActObjServant_HPP_ */
