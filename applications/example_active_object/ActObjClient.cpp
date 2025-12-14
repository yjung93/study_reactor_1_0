
#include "ActObjClient.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;

namespace ExActiveObject
{
ActObjClient::ActObjClient( int socketFd )
    : mSocketFd( socketFd )
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

void ActObjClient::processMessage( const std::string &message )
{
    cout << "ActObjClient::"
         << __FUNCTION__
         << endl;

    string messageToSend = mServantProxy.requestGetReturnMessageSync( message );
    send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
}
} // namespace ExActiveObject