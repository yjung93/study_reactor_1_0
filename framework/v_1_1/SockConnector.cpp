/*
 * SockConnector.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */
#include "SockConnector.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

using namespace std;

namespace v_1_1
{

constexpr int PORT = 8080;
constexpr int BACKLOG = 5;

SockConnector::SockConnector( v_1_1::Reactor *reactor ) :
                mHandle( 0 )
{
    cout << "SockConnector::"
         << __FUNCTION__
         << ": "
         << endl;
}

SockConnector::~SockConnector()
{
    cout << "SockConnector::"
         << __FUNCTION__
         << ": "
         << endl;
}

void SockConnector::setHandle( int handle )
{
    cout << "SockConnector::"
         << __FUNCTION__
         << ": "
         << endl;

    mHandle = handle;
}
int SockConnector::getHandle()
{
    cout << "SockConnector::"
         << __FUNCTION__
         << ": "
         << endl;

    return mHandle;
}

int SockConnector::connect( SockStream &newStream, const PEER_ADDR &remoteAddr, int reuse_addr, int flags, int perms, int protocol )
{
    cout << "SockConnector::"
         << __FUNCTION__
         << ": "
         << endl;

    int result = 0;

    result = open( newStream, remoteAddr.sin_family, protocol, reuse_addr );
    if ( result != -1 )
    {
        result = connectStart( newStream );
    }

    if ( result != -1 )
    {
        result = ::connect( newStream.getHandle(),
                            (struct sockaddr*) &remoteAddr,
                            sizeof(remoteAddr) );
    }

    return connectFinish( newStream, result );
}

int SockConnector::open( SockStream &newStream, int protocolFamily, int protocol, int reuseAddr )
{
    int result = 0;
    cout << "SockConnector::"
         << __FUNCTION__
         << ": "
         << endl;

    // Only open a new socket if we don't already have a valid handle.
    if ( (newStream.getHandle() == INVALID_HANDLE)
         && (newStream.open( SOCK_STREAM, protocolFamily, protocol, reuseAddr )
             == -1) )
    {
        result = -1;
    }else
    {
        result = 0;
    }

    return result;
}

int SockConnector::connectStart( SockStream &new_stream )
{
    int result = 0;

    // TBD

    return result;
}

int SockConnector::connectFinish( SockStream &new_stream, int result )
{
    int returnVaue = 0;

    // TBD

    returnVaue = result;
    return returnVaue;
}

} /* namespace example_reactor */
