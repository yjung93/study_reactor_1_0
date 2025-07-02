/*
 * ConnectorImpl.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include <applications/example_acceptor_connector/ConnectorImpl.hpp>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

namespace ex_acceptor_connector
{

constexpr int PORT = 8080;

ConnectorImpl::ConnectorImpl( Reactor_1_0::Reactor *reactor ) :
                PARENT( reactor, 0 )

{


}

ConnectorImpl::~ConnectorImpl()
{
}

} /* namespace ex_acceptor_connector */

