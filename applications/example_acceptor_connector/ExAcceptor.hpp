/*
 * ExAcceptor.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_EXACCEPTOR_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_EXACCEPTOR_HPP_

#include "framework/v_1_1/Acceptor.hpp"
#include "framework/v_1_1/SockAcceptor.hpp"
#include "InputHandler.hpp"

namespace ex_acceptor_connector
{

class ExAcceptor: public v_1_1::Acceptor<InputHandler, v_1_1::SockAcceptor>
{
public:
    typedef v_1_1::Acceptor<InputHandler, v_1_1::SockAcceptor> PARENT;
    ExAcceptor( v_1_1::Reactor *reactor );
    virtual ~ExAcceptor();
};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_EXACCEPTOR_HPP_ */
