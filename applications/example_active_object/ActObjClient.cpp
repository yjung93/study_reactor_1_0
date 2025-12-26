
#include "ActObjClient.hpp"
#include "ActObjMethodCallback.hpp"

#include <iostream>
#include <sys/socket.h>

using namespace std;

namespace ExActiveObject
{
ActObjClient::ActObjClient( int socketFd )
    : mSocketFd( socketFd ),
      mUsecaseItterate( 0 )
{
    cout << "ActObjClient::"
         << __FUNCTION__
         << endl;
}
ActObjClient::~ActObjClient()
{
    cout << "ActObjClient::"
         << __FUNCTION__
         << endl;
}

int ActObjClient::open( void *args )
{
    cout << "ActObjClient::"
         << __FUNCTION__
         << endl;

    return activate();
}
int ActObjClient::svc()
{
    cout << "ActObjClient::"
         << __FUNCTION__
         << endl;

    string message;
    while ( getQ( message ) == 0 )
    {
        processMessage( message );
    }

    return 0;
}

int ActObjClient::getHandle()
{
    return mSocketFd;
}

void ActObjClient::processMessage( const std::string &message )
{
    cout << "ActObjClient::"
         << __FUNCTION__
         << endl;

    string messageToSend = "Unknown Error";

    unsigned int usecase = mUsecaseItterate % 3;
    mUsecaseItterate++;

    switch ( usecase )
    {
        case 0: // sync timeout 2s
        {
            ActiveObject_1_0::Future<string> future = mServantProxy.requestGetReturnMessage( message );

            int rc = future.get( messageToSend, 2000 );
            if ( rc == -1 )
            {
                messageToSend = "Request Timeout";
            }
            send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
            break;
        }
        case 1: // sync timeout 500ms
        {
            ActiveObject_1_0::Future<string> future = mServantProxy.requestGetReturnMessage( message );

            int rc = future.get( messageToSend, 500 );
            if ( rc == -1 )
            {
                messageToSend = "Request Timeout";
            }
            send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
            break;
        }
        case 2: // async.
        {
            ActiveObject_1_0::Future<string> future = mServantProxy.requestGetReturnMessage( message );
            future.attach( new CallbackGetReturnMessage( *this ) );
            break;
        }
        default:
        {
            break;
        }
    }
}
} // namespace ExActiveObject