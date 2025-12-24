#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjMethodRequests_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjMethodRequests_HPP_

#include "framework/active_object/1_0/MethodRequest.hpp"
#include "framework/active_object/1_0/Future.hpp"

#include "ActObjServant.hpp"

using namespace std;

namespace ExActiveObject
{

class RequestGetReturnMessage : public ActiveObject_1_0::MethodRequest
{
  public:
    RequestGetReturnMessage( ActObjServant &Servant,
                             ActiveObject_1_0::Future<string> &returnVal,
                             const string &message );
    int call() override;

  private:
    ActObjServant &mServant;
    ActiveObject_1_0::Future<string> mReturnValue;
    string  mMessage;
};

} // namespace ExActiveObject

#endif //#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_ActObjMethodRequests_HPP_