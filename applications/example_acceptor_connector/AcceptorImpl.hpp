/*
 * AcceptorImpl.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_AcceptorImpl_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_AcceptorImpl_HPP_

#include "framework/acceptor_connector/1_0/Acceptor.hpp"
#include "framework/acceptor_connector/1_0/SockAcceptor.hpp"
#include "InputHandler.hpp"

namespace ex_acceptor_connector
{

class AcceptorImpl: public AcceptorConnector_1_0::Acceptor<InputHandler, AcceptorConnector_1_0::SockAcceptor>
{
public:
    typedef AcceptorConnector_1_0::Acceptor<InputHandler, AcceptorConnector_1_0::SockAcceptor> PARENT;
    AcceptorImpl( Reactor_1_0::Reactor *reactor );
    virtual ~AcceptorImpl();
};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_AcceptorImpl_HPP_ */
