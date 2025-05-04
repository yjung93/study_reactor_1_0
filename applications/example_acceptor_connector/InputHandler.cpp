/*
 * InputHandler.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "InputHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"

using namespace std;

namespace ex_acceptor_connector
{

InputHandler::InputHandler() :
                EventHandler( v_1_1::Reactor::getInstance() ),
                mHandle( 0 )
{
    cout << "InputHandler::"
         << __FUNCTION__
         << ": "
         << endl;
}

InputHandler::~InputHandler()
{
    cout << "InputHandler::"
         << __FUNCTION__
         << ": "
         << endl;
}

int InputHandler::open( void* )
{
    int result = 0;
    cout << "InputHandler::"
         << __FUNCTION__
         << ": "
         << endl;

    getReactor()->registerHandler( this, EventHandler::READ_MASK );
    return result;
}

int InputHandler::handleInput( int fd )
{
    cout << "InputHandler::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] =
    { 0 };

    int valread = read( fd, buffer, bufferSize );
    if ( valread == 0 )
    {
        // Client disconnected
        cout << "InputHandler::"
             << __FUNCTION__
             << ": "
             << "Client disconnected, socket FD: "
             << fd
             << endl;
        ::close( fd );
        getReactor()->removeHandler( this );
    }else
    {
        // Echo the message back to client
        cout << "InputHandler::"
             << __FUNCTION__
             << ": "
             << "Received message: "
             << buffer
             << endl;

        string messageToSend = "Echo - " + string( buffer );
        send( fd, messageToSend.c_str(), messageToSend.size(), 0 );

        cout << "InputHandler::"
             << __FUNCTION__
             << ": "
             << "Replied message: "
             << messageToSend
             << endl;
    }

    return 0;
}

int InputHandler::close()
{
    int result = 0;
    cout << "InputHandler::"
         << __FUNCTION__
         << ": "
         << endl;
    return result;
}

} /* namespace ex_acceptor_connector */
