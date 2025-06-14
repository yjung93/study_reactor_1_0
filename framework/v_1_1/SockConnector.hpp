/*
 * SockConnector.hpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_SockConnector_HPP_
#define FRAMEWORK_V_1_1_SockConnector_HPP_

#include <arpa/inet.h>

#include "framework/v_1_1/EventHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"
#include "framework/v_1_1/SockStream.hpp"

namespace v_1_1
{

class SockConnector
{
public:
    typedef struct sockaddr_in PEER_ADDR;

    SockConnector( v_1_1::Reactor *reactor = v_1_1::Reactor::getInstance() );
    virtual ~SockConnector();

    int connect( SockStream &new_stream, const PEER_ADDR &remoteAddr, int reuse_addr =
                    0, int flags = 0, int perms = 0, int protocol = 0 );
    void setHandle( int handle );
    int getHandle();

protected:

    int open( SockStream &newStream, int protocolFamily, int protocol, int reuseAddr );

    int connectStart( SockStream &new_stream );

    int connectFinish( SockStream &new_stream, int result );

private:
    PEER_ADDR mAddress;
    int mHandle;
};

} /* namespace example_reactor */

#endif /* APPLICATIONS_EXAMPLE_REACTOR_ACCEPTOR_HPP_ */
