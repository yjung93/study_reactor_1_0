/*
 * SockStream.cpp
 *
 *  Created on: May 9, 2025
 *      Author: yjung93
 */

#include <iostream>
#include <unistd.h>

#include "Config.hpp"
#include "SockStream.hpp"

using namespace std;

namespace v_1_1
{

SockStream::SockStream() :
                mHandle( INVALID_HANDLE )
{
    // TODO Auto-generated constructor stub

}

SockStream::~SockStream()
{
    // TODO Auto-generated destructor stub
}

void SockStream::setHandle( int handle )
{
    mHandle = handle;
}
int SockStream::getHandle() const
{
    return mHandle;
}

ssize_t SockStream::recv_n( void *buf, size_t size, int flags )
{
    return ::recv( getHandle(), buf, size, flags );
}

ssize_t SockStream::send_n( const void *buf, size_t size, int flags )
{
    return ::send( getHandle(), buf, size, flags );
}

int SockStream::close_reader()
{
    return ::shutdown( getHandle(), SHUT_RD );
}
int SockStream::close_writer()
{
    return ::shutdown( getHandle(), SHUT_WR );
}

int SockStream::open( int type, int protocolFamily, int protocol, int reuseAddr )
{

    int result = 0;

    setHandle( socket( protocolFamily, type, protocol ) );

    if ( this->getHandle() == INVALID_HANDLE )
    {
        result = -1;
    }

    cout << "SockStream::"
         << __FUNCTION__
         << ": "
         << " handle : "
         << getHandle()
         << endl;

    return result;
}

} /* namespace v_1_1 */
