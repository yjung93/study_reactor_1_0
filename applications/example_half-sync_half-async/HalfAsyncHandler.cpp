/*
 * HalfAsyncHandler.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#include "applications/example_half-sync_half-async/HalfAsyncHandler.hpp"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

namespace ExHalfSyncAsync
{

HalfAsyncHandler::HalfAsyncHandler( Reactor_1_0::Reactor *reactor )
    : EventHandler( reactor )
{
    cout << "HalfAsyncHandler::"
         << __FUNCTION__
         << endl;
}

HalfAsyncHandler::~HalfAsyncHandler()
{
    cout << "HalfAsyncHandler::"
         << __FUNCTION__
         << endl;

    if ( mHalfSyncHandler != nullptr )
    {
        delete mHalfSyncHandler;
    }
}

void HalfAsyncHandler::open()
{
    cout << "HalfAsyncHandler::"
         << __FUNCTION__
         << endl;
    getReactor()->registerHandler( this, EventHandler::READ_MASK );

    // Initialize HalfSyncHandler
    mHalfSyncHandler = new HalfSyncHandler( getHandle() );
    mHalfSyncHandler->open();
}

int HalfAsyncHandler::handleInput( int fd )
{
    cout << "HalfAsyncHandler::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] = { 0 };

    int valread = read( fd, buffer, bufferSize );
    if ( valread == 0 )
    {
        // Client disconnected
        cout << "Client disconnected, socket FD: "
             << fd
             << endl;
        close( fd );
        getReactor()->removeHandler( this, ALL_EVENTS_MASK );
    }
    else
    {
        // Echo the message back to client
        cout << "Received message: "
             << buffer
             << endl;

        mHalfSyncHandler->putQ( string( buffer ) );
    }

    return 0;
}

} /* namespace  ExHalfSyncAsync */
