
#include "HalfSyncHandler.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;
HalfSyncHandler::HalfSyncHandler( int socketFd )
    : mSocketFd( socketFd )
{
    cout << "HalfSyncHandler::"
         << __FUNCTION__
         << endl;
}
HalfSyncHandler::~HalfSyncHandler()
{
    cout << "HalfSyncHandler::"
         << __FUNCTION__
         << endl;
}

int HalfSyncHandler::open( void *args )
{
    cout << "HalfSyncHandler::"
         << __FUNCTION__
         << endl;

    return activate();
}
int HalfSyncHandler::svc()
{
    cout << "HalfSyncHandler::"
         << __FUNCTION__
         << endl;

    string message;
    while ( getQ( message ) == 0 )
    {
        processMessage( message );
    }

    return 0;
}

void HalfSyncHandler::processMessage( const std::string &message )
{
    cout << "HalfSyncHandler::"
         << __FUNCTION__
         << endl;

    string messageToSend = "Echo - " + message;
    send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
}