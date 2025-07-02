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
#include <sys/socket.h>
#include "InputHandler.hpp"
#include "framework/reactor/1_0/Reactor.hpp"

using namespace std;

namespace ex_acceptor_connector
{

InputHandler::InputHandler() :
                ServiceHandler( Reactor_1_0::Reactor::getInstance() )
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

int InputHandler::handleInput( int fd )
{
    cout << "InputHandler::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] =
    { 0 };

    int valread = peer().recv_n( buffer, bufferSize, 0 );
    if ( valread == 0 )
    {
        // Client disconnected
        cout << "InputHandler::"
             << __FUNCTION__
             << ": "
             << "Client disconnected, socket FD: "
             << fd
             << endl;
        peer().close_reader();
        getReactor()->removeHandler( this, ALL_EVENTS_MASK );
    }else if ( valread < 0 )
    {
        perror( "recv failed" );
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
        peer().send_n( messageToSend.c_str(), messageToSend.size(), 0 );
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

