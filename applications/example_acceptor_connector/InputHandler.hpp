/*
 * InputHandler.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_INPUTHANDLER_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_INPUTHANDLER_HPP_

#include "framework/v_1_1/ServiceHandler.hpp"
#include "framework/v_1_1/SockStream.hpp"

namespace ex_acceptor_connector
{

class InputHandler: public v_1_1::ServiceHandler<v_1_1::SockStream>
{
public:
    InputHandler();
    virtual ~InputHandler();

    int close();

private:
    int handleInput( int fd = INVALID_HANDLE ) override;
};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_INPUTHANDLER_HPP_ */
