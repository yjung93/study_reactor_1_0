#include <iostream>

#include "ActObjMethodRequests.hpp"

namespace ExActiveObject
{

RequestGetReturnMessage::RequestGetReturnMessage( ActObjServant &Servant,
                                                  ActiveObject_1_0::Future<string> &returnVal,
                                                  const string &message )
    : mServant( Servant ),
      mReturnValue( returnVal ),
      mMessage( message )
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;
}

int RequestGetReturnMessage::call()
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;

    // status_update with the controller.
    this->mReturnValue.set( this->mServant.RequestGetReturnMessage( mMessage ) );
    return 0;
}

} // namespace ExActiveObject