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
    cout << "SockAcceptor::"
         << __FUNCTION__
         << ": "
         << endl;
}

SockAcceptor::~SockAcceptor()
{
    cout << "SockAcceptor::"
         << __FUNCTION__
         << ": "
         << endl;
}

int SockAcceptor::open( PEER_ADDR peerAddr )
{
    cout << "SockAcceptor::"
         << __FUNCTION__
         << ": "
         << endl;

    int acceptorFd;
    int opt = 1;
    int result = 0;

    mAddress = peerAddr;

    if ( result != -1 && (acceptorFd = socket( AF_INET, SOCK_STREAM, 0 )) == 0 )
    {
        cout << "SockAcceptor::"
             << __FUNCTION__
             << ": "
             << "socket failed"
             << endl;

        result = -1;
    }

    // Set socket options
    if ( result != -1
         && setsockopt( acceptorFd,
         SOL_SOCKET,
                        ( SO_REUSEADDR | SO_REUSEPORT), &opt, sizeof(opt) )
            == -1 )
    {

        cout << "SockAcceptor::"
             << __FUNCTION__
             << ": "
             << "setsockopt failed"
             << endl;

        close( acceptorFd );
        result = -1;
    }

    // Bind the socket to the network address and port
    if ( result != -1
         && bind( acceptorFd, (struct sockaddr*) &mAddress, sizeof(mAddress) )
            < 0 )
    {

        cout << "SockAcceptor::"
             << __FUNCTION__
             << ": "
             << "bind failed"
             << endl;

        close( acceptorFd );
        result = -1;
    }

    // Listen for incoming connections
    if ( result != -1 && listen( acceptorFd, BACKLOG ) < 0 )
    {

        cout << "SockAcceptor::"
             << __FUNCTION__
             << ": "
             << "listen failed"
             << endl;

        close( acceptorFd );
        result = -1;
    }

    if ( result != -1 )
    {
        setHandle( acceptorFd );

        cout << "SockAcceptor::"
             << __FUNCTION__
             << ": "
             << "Server listening on port "
             << PORT
             << " acceptorFd="
             << acceptorFd
             << endl;
    }

    return result;

}

int SockAcceptor::accept( int fd )
{
    cout << "SockAcceptor::"
         << __FUNCTION__
         << ": "
         << "fd="
         << fd
         << endl;

    socklen_t addrlen = sizeof(mAddress);
    int result = 0;

    int newSocketFd = ::accept( fd, (struct sockaddr*) &mAddress, &addrlen );
    if ( newSocketFd < 0 )
    {
        cout << "SockAcceptor::"
             << __FUNCTION__
             << ": "
             << "accept failed"
             << " fd="
             << fd
             << endl;
        result = -1;
    }

    return (result != -1) ? newSocketFd : result;
}

void SockAcceptor::setHandle( int handle )
{
    cout << "SockAcceptor::"
         << __FUNCTION__
         << ": "
         << endl;

    mHandle = handle;
}
int SockAcceptor::getHandle()
{
    cout << "SockAcceptor::"
         << __FUNCTION__
         << ": "
         << endl;

    return mHandle;
}

} /* namespace example_reactor */
