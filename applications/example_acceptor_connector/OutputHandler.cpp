/*
 * OutputHandler.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include "OutputHandler.hpp"
#include "framework/reactor/1_0/Reactor.hpp"

using namespace std;

namespace ex_acceptor_connector
{

OutputHandler::OutputHandler() :
                ServiceHandler( Reactor_1_0::Reactor::getInstance() )
{
    cout << "OutputHandler::"
         << __FUNCTION__
         << ": "
         << endl;
}

OutputHandler::~OutputHandler()
{
    cout << "OutputHandler::"
         << __FUNCTION__
         << ": "
         << endl;
}

int OutputHandler::handleInput( int fd )
{
    cout << "OutputHandler::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] =
    { 0 };

    int valread = peer().recv_n( buffer, bufferSize, 0 );
    if ( valread == 0 )
    {
        // Client disconnected
        cout << "OutputHandler::"
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
        cout << "OutputHandler::"
             << __FUNCTION__
             << ": "
             << "Received message: "
             << buffer
             << endl;

    }

    return 0;
}

int OutputHandler::handleOutput( int fd )
{
    cout << "OutputHandler::"
         << __FUNCTION__
         << endl;

//    open((void*)this);
    return 0;
}

int OutputHandler::close()
{
    int result = 0;
    cout << "OutputHandler::"
         << __FUNCTION__
         << ": "
         << endl;
    return result;
}

void OutputHandler::sendMessage( string message )
{
    peer().send_n( message.c_str(), message.size(), 0 );
}

} /* namespace ex_acceptor_connector */

