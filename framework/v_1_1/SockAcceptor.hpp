/*
 * SockAcceptor.hpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_SOCKACCEPTOR_HPP_
#define FRAMEWORK_V_1_1_SOCKACCEPTOR_HPP_

#include <arpa/inet.h>

#include "framework/v_1_1/EventHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"
#include "framework/v_1_1/SockStream.hpp"

namespace v_1_1
{

class SockAcceptor
{
public:
    typedef struct sockaddr_in PEER_ADDR;

    SockAcceptor( v_1_1::Reactor *reactor = v_1_1::Reactor::getInstance() );
    virtual ~SockAcceptor();

    int open( PEER_ADDR peerAddr );
    int accept( SockStream &newStream, int fd );
    void setHandle( int handle );
    int getHandle();

private:
    PEER_ADDR mAddress;
    int mHandle;
};

} /* namespace example_reactor */

#endif /* APPLICATIONS_EXAMPLE_REACTOR_ACCEPTOR_HPP_ */
