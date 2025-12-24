#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServantProxy_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServantProxy_HPP_

#include "framework/active_object/1_0/Future.hpp"

#include "ActObjServant.hpp"
#include "ActObjScheduler.hpp"

using namespace std;

namespace ExActiveObject
{

class ActObjServantProxy
{
  public:
    ActObjServantProxy();
    ~ActObjServantProxy();
    ActiveObject_1_0::Future<string> requestGetReturnMessageSync( const string &message );

  private:
    ActObjScheduler mScheduler;
    ActObjServant mServant;
};

} // namespace ExActiveObject

#endif //#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjServantProxy_HPP_
