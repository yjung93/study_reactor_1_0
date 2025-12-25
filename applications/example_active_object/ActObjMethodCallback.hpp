#ifndef APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_CallbackGetReturnMessage_HPP_
#define APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_CallbackGetReturnMessage_HPP_

#include "framework/active_object/1_0/Future.hpp"

#include "ActObjServantProxy.hpp"

namespace ExActiveObject
{

class ActObjClient;

class CallbackGetReturnMessage : public ActiveObject_1_0::FutureObserver<string>
{
  public:
    CallbackGetReturnMessage( ActObjClient &parent );

    void update( const ActiveObject_1_0::Future<string> &future ) override;

  private:
    ActObjClient &mParent;
};

} // namespace ExActiveObject

#endif // APPLICATIONS_EXAMPLE_ACTIVE_OBJECT_CallbackGetReturnMessage_HPP_