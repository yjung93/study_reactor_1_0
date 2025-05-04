/*
 * InputHandler.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_INPUTHANDLER_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_INPUTHANDLER_HPP_

#include "framework/v_1_1/EventHandler.hpp"

namespace ex_acceptor_connector
{

class InputHandler: public v_1_1::EventHandler
{
public:
    InputHandler();
    virtual ~InputHandler();

    int open( void* );
    int close();

private:
    int handleInput( int fd = INVALID_HANDLE ) override;
    int mHandle;
};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_INPUTHANDLER_HPP_ */
