/*
 * AsyncService.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#include "applications/example_half-sync_half-async/AsyncService.hpp"
#include "applications/example_half-sync_half-async/Acceptor.hpp"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

namespace ExHalfSyncAsync
{

AsyncService::AsyncService( Reactor_1_0::Reactor *reactor, Acceptor &owner )
    : EventHandler( reactor ),
      mOwner( &owner )
{
    cout << "AsyncService::"
         << __FUNCTION__
         << endl;
}

AsyncService::~AsyncService()
{
    cout << "AsyncService::"
         << __FUNCTION__
         << endl;
}

void AsyncService::open()
{
    cout << "AsyncService::"
         << __FUNCTION__
         << endl;
    getReactor()->registerHandler( this, EventHandler::READ_MASK );

    // Initialize SyncService
    mSyncService.reset( new SyncService( getHandle() ) );
    mSyncService->open();
}

int AsyncService::handleInput( int fd )
{
    cout << "AsyncService::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] = { 0 };

    int valread = read( fd, buffer, bufferSize );
    if ( valread <= 0 )
    {
        if ( valread == 0 )
        {
            cout << "Client disconnected, socket FD: "
                 << fd
                 << endl;
        }
        else
        {
            perror( "read failed" );
        }

        close( fd );
        getReactor()->removeHandler( this, ALL_EVENTS_MASK );
        if ( mOwner != nullptr )
        {
            mOwner->removeConnection( fd );
        }
        // return here immediately to avoid further processing since this object is likely destroyed.
        return 0;
    }

    cout << "Received message: "
         << buffer
         << endl;

    mSyncService->putQ( string( buffer, static_cast<size_t>( valread ) ) );

    return 0;
}

} /* namespace  ExHalfSyncAsync */
