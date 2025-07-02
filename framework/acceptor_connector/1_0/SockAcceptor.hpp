/*
 * SockAcceptor.hpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef FRAMEWORK_ACCEPTOR_CONNECTOR_1_0_SOCKACCEPTOR_HPP_
#define FRAMEWORK_ACCEPTOR_CONNECTOR_1_0_SOCKACCEPTOR_HPP_

#include <arpa/inet.h>

#include "framework/reactor/1_0/EventHandler.hpp"
#include "framework/reactor/1_0/Reactor.hpp"
#include "framework/acceptor_connector/1_0/SockStream.hpp"

namespace AcceptorConnector_1_0
{

class SockAcceptor
{
public:
    typedef struct sockaddr_in PEER_ADDR;

    SockAcceptor( Reactor_1_0::Reactor *reactor = Reactor_1_0::Reactor::getInstance() );
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
