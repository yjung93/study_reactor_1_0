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

using namespace std;

namespace example_1
{

ServerEventHandler::ServerEventHandler( v_1_0::Reactor *reactor ) :
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

    char buffer[1024] =
    { 0 };
    int valread = read( fd, buffer, 1024 );
    if ( valread == 0 )
    {
        // Client disconnected
        cout << "Client disconnected, socket FD: "
             << fd
             << endl;
        close( fd );
        getReactor()->removeHandler( this );
    }else
    {
        // Echo the message back to client
        cout << "Received message: "
             << buffer
             << endl;
        send( fd, "Message received", strlen( "Message received" ), 0 );
    }

    return 0;
}

} /* namespace example_1 */
