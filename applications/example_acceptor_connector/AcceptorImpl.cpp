/*
 * AcceptorImpl.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include "AcceptorImpl.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
namespace ex_acceptor_connector
{

constexpr int PORT = 8080;

AcceptorImpl::AcceptorImpl( Reactor_1_0::Reactor *reactor ) :
                PARENT( reactor, 0 )

{
    AcceptorConnector_1_0::SockAcceptor::PEER_ADDR peerAddr;
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_addr.s_addr = INADDR_ANY;
    peerAddr.sin_port = htons( PORT );

    open( peerAddr );

}

AcceptorImpl::~AcceptorImpl()
{
}

} /* namespace ex_acceptor_connector */

