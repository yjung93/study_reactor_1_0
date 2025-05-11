/*
 * SockStream.cpp
 *
 *  Created on: May 9, 2025
 *      Author: yjung93
 */

#include "SockStream.hpp"

namespace v_1_1
{

SockStream::SockStream()
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

} /* namespace v_1_1 */
