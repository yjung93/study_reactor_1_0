/*
 * ServerEventHandler.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#include "applications/example_proactor/ServerEventHandler.hpp"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

namespace example_proactor_old
{

ServerEventHandler::ServerEventHandler( Reactor_1_0::Reactor *reactor ) :
                EventHandler( reactor )
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

void ServerEventHandler::open()
{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << endl;
    getReactor()->registerHandler( this, EventHandler::READ_MASK );
}

int ServerEventHandler::handleInput( int fd )
{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] =
    { 0 };

    int valread = read( fd, buffer, bufferSize );
    if ( valread == 0 )
    {
        // Client disconnected
        cout << "Client disconnected, socket FD: "
             << fd
             << endl;
        close( fd );
        getReactor()->removeHandler( this, ALL_EVENTS_MASK );
    }else
    {
        // Echo the message back to client
        cout << "Received message: "
             << buffer
             << endl;

        string messageToSend = "Echo - " + string( buffer );
        send( fd, messageToSend.c_str(), messageToSend.size(), 0 );

        cout << "Replied message: "
             << messageToSend
             << endl;
    }

    return 0;
}

} /* namespace example_proactor */
