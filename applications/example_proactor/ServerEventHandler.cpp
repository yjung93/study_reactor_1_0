/*
 * ServerEventHandler.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ServerEventHandler.hpp"
#include "Acceptor.hpp"

using namespace std;

namespace example_proactor
{

ServerEventHandler::ServerEventHandler( Acceptor &owner )
    : mOwner( &owner ),
      mMessage( 1024 )

{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << endl;
}

ServerEventHandler::~ServerEventHandler()
{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << endl;
}

void ServerEventHandler::open( int new_handle )
{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << ": "
         << endl;

    mReader.open( *this, new_handle, 0, proactor() );
    mReader.read( mMessage, mMessage.size() );
}

// int ServerEventHandler::handleInput( int fd )
// {
//     cout << "ServerEventHandler::"
//          << __FUNCTION__
//          << endl;

//     const int bufferSize = 1024;

//     char buffer[bufferSize] = { 0 };

//     int valread = read( fd, buffer, bufferSize );
//     if ( valread == 0 )
//     {
//         // Client disconnected
//         cout << "Client disconnected, socket FD: "
//              << fd
//              << endl;

//         close( fd );
//         getReactor()->removeHandler( this, ALL_EVENTS_MASK );

//         if ( mOwner != nullptr )
//         {
//             mOwner->removeConnection( fd );
//         }
//     }
//     else
//     {
//         // Echo the message back to client
//         cout << "Received message: "
//              << buffer
//              << endl;

//         string messageToSend = "Echo - " + string( buffer );
//         send( fd, messageToSend.c_str(), messageToSend.size(), 0 );

//         cout << "Replied message: "
//              << messageToSend
//              << endl;
//     }

//     return 0;
// }

void ServerEventHandler::handle_read_stream( const Proactor_1_0::AsynchReadStreamResult &result )
{
    string messageReceived( result.message().begin(), result.message().begin() + result.bytes_transferred() );
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << ": "
         << "received="
         << messageReceived
         << endl;

    string messageToSend = "Echo - " + string( messageReceived );
    send( result.aio_fildes, messageToSend.c_str(), messageToSend.size(), 0 );

    cout << "Replied message: "
         << messageToSend
         << endl;

    mReader.read( mMessage, mMessage.size() );
}
} /* namespace example_proactor */
