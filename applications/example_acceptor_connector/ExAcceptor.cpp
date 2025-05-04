/*
 * ExAcceptor.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include "ExAcceptor.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
namespace ex_acceptor_connector
{

constexpr int PORT = 8080;

ExAcceptor::ExAcceptor( v_1_1::Reactor *reactor ) :
                PARENT( reactor, 0 )

{
    v_1_1::SockAcceptor::PEER_ADDR peerAddr;
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_addr.s_addr = INADDR_ANY;
    peerAddr.sin_port = htons( PORT );

    open( peerAddr );

}

ExAcceptor::~ExAcceptor()
{
}

} /* namespace ex_acceptor_connector */

