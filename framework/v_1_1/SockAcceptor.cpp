/*
 * SockAcceptor.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */
#include "SockAcceptor.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

using namespace std;

namespace v_1_1
{

constexpr int PORT = 8080;
constexpr int BACKLOG = 5;

SockAcceptor::SockAcceptor( v_1_1::Reactor *reactor ) :
                mHandle( 0 )
{

}

SockAcceptor::~SockAcceptor()
{
}

int SockAcceptor::open( PEER_ADDR peerAddr )
{

    int acceptorFd;
    int opt = 1;

    mAddress = peerAddr;

    if ( (acceptorFd = socket( AF_INET, SOCK_STREAM, 0 )) == 0 )
    {
        perror( "socket failed" );
        exit( EXIT_FAILURE );
    }

    // Set socket options
    if ( setsockopt( acceptorFd,
    SOL_SOCKET,
                     ( SO_REUSEADDR | SO_REUSEPORT), &opt, sizeof(opt) )

         == -1 )
    {
        perror( "setsockopt failed" );
        close( acceptorFd );
        exit( EXIT_FAILURE );
    }

    // Bind the socket to the network address and port
    if ( bind( acceptorFd, (struct sockaddr*) &mAddress, sizeof(mAddress) )
         < 0 )
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

    setHandle( acceptorFd );

    return -1;

}

int SockAcceptor::accept( int fd )
{
    socklen_t addrlen = sizeof(mAddress);

    int newSocketFd = ::accept( fd, (struct sockaddr*) &mAddress, &addrlen );

    if ( newSocketFd < 0 )
    {
        perror( "accept failed" );
        exit( EXIT_FAILURE );
    }
    return 0;
}

void SockAcceptor::setHandle( int handle )
{
    mHandle = handle;
}
int SockAcceptor::getHandle()
{
    return mHandle;
}

} /* namespace example_reactor */
