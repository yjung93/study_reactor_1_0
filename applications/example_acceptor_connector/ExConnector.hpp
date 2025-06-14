/*
 * ExConnector.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_ExConnector_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_ExConnector_HPP_

#include "framework/v_1_1/Connector.hpp"
#include "framework/v_1_1/SockConnector.hpp"

#include "OutputHandler.hpp"

namespace ex_acceptor_connector
{

class ExConnector: public v_1_1::Connector<OutputHandler, v_1_1::SockConnector>
{
public:
    typedef v_1_1::Connector<OutputHandler, v_1_1::SockConnector> PARENT;

    ExConnector( v_1_1::Reactor *reactor = v_1_1::Reactor::getInstance() );
    ~ExConnector();

};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_ExConnector_HPP_ */
