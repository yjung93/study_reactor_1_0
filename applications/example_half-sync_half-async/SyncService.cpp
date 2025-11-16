
#include "SyncService.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;
SyncService::SyncService( int socketFd )
    : mSocketFd( socketFd )
{
    cout << "SyncService::"
         << __FUNCTION__
         << endl;
}
SyncService::~SyncService()
{
    cout << "SyncService::"
         << __FUNCTION__
         << endl;
}

int SyncService::open( void *args )
{
    cout << "SyncService::"
         << __FUNCTION__
         << endl;

    return activate();
}
int SyncService::svc()
{
    cout << "SyncService::"
         << __FUNCTION__
         << endl;

    string message;
    while ( getQ( message ) == 0 )
    {
        processMessage( message );
    }

    return 0;
}

void SyncService::processMessage( const std::string &message )
{
    cout << "SyncService::"
         << __FUNCTION__
         << endl;

    string messageToSend = "Echo - " + message;
    send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
}