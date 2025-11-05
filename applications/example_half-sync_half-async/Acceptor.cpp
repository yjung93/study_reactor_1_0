/*
 * Acceptor.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */
#include "applications/example_half-sync_half-async/Acceptor.hpp"
#include "applications/example_half-sync_half-async/HalfAsyncHandler.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

using namespace std;

namespace ExHalfSyncAsync
{

constexpr int PORT = 8080;
constexpr int BACKLOG = 5;

Acceptor::Acceptor( Reactor_1_0::Reactor *reactor )
    : EventHandler( reactor )
{
    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = INADDR_ANY;
    mAddress.sin_port = htons( PORT );

    open();
}

Acceptor::~Acceptor()
{
    // TODO Auto-generated destructor stub
}

void Acceptor::open()
{
    int acceptorFd;
    int opt = 1;

    if ( ( acceptorFd = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 )
    {
        perror( "socket failed" );
        exit( EXIT_FAILURE );
    }

    setHandle( acceptorFd );

    // Set socket options
    if ( setsockopt( acceptorFd, SOL_SOCKET, ( SO_REUSEADDR | SO_REUSEPORT ), &opt, sizeof( opt ) ) == -1 )
    {
        perror( "setsockopt failed" );
        close( acceptorFd );
        exit( EXIT_FAILURE );
    }

    // Bind the socket to the network address and port
    if ( bind( acceptorFd, (struct sockaddr *) &mAddress, sizeof( mAddress ) ) < 0 )
    {
        perror( "bind failed" );
        close( acceptorFd );
        exit( EXIT_FAILURE );
    }

    // Listen for incoming connections
    if ( listen( acceptorFd, BACKLOG ) < 0 )
    {
        perror( "listen failed" );
        close( acceptorFd );
        exit( EXIT_FAILURE );
    }

    std::cout << "Server listening on port "
              << PORT
              << std::endl;

    getReactor()->registerHandler( this, EventHandler::ACCEPT_MASK );
}

int Acceptor::handleInput( int fd )
{
    cout << __FUNCTION__
         << endl;

    int addrlen = sizeof( mAddress );
    int newSocketFd = accept( fd, (struct sockaddr *) &mAddress, (socklen_t *) &( addrlen ) );

    if ( newSocketFd < 0 )
    {
        perror( "accept failed" );
        exit( EXIT_FAILURE );
    }

    HalfAsyncHandler *HalfAsyncHandler = new ExHalfSyncAsync::HalfAsyncHandler( getReactor() );
    HalfAsyncHandler->setHandle( newSocketFd );
    HalfAsyncHandler->open();

    std::cout << "New connection established, socket FD: "
              << newSocketFd
              << std::endl;
    return 0;
}

} /* namespace  ExHalfSyncAsync */
