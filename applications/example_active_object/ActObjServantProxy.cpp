#include <iostream>

#include "ActObjServantProxy.hpp"
#include "ActObjMethodRequests.hpp"

namespace ExActiveObject
{

ActObjServantProxy::ActObjServantProxy()
{
}

ActObjServantProxy::~ActObjServantProxy()
{
}

ActiveObject_1_0::Future<string> ActObjServantProxy::requestGetReturnMessageSync( const string &message )
{
    cout << "ActObjServantProxy::"
         << __FUNCTION__
         << endl;

    ActiveObject_1_0::Future<string> result;
    ActiveObject_1_0::MethodRequest *methodRequest = new RequestGetReturnMessage( mServant, result, message );

    mScheduler.enqueue( methodRequest );

    return result;
}

} // namespace ExActiveObject