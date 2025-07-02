/*
 * ConnectorImpl.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_ExConnector_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_ExConnector_HPP_

#include "framework/acceptor_connector/1_0/Connector.hpp"
#include "framework/acceptor_connector/1_0/SockConnector.hpp"

#include "OutputHandler.hpp"

namespace ex_acceptor_connector
{

class ConnectorImpl: public AcceptorConnector_1_0::Connector<OutputHandler, AcceptorConnector_1_0::SockConnector>
{
public:
    typedef AcceptorConnector_1_0::Connector<OutputHandler, AcceptorConnector_1_0::SockConnector> PARENT;

    ConnectorImpl( Reactor_1_0::Reactor *reactor = Reactor_1_0::Reactor::getInstance() );
    ~ConnectorImpl();

};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_ExConnector_HPP_ */
