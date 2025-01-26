/*
 * InputHandler.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include "InputHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"

namespace ex_acceptor_connector
{

InputHandler::InputHandler() :
                EventHandler( v_1_1::Reactor::getInstance() )
{
    // TODO Auto-generated constructor stub

}

InputHandler::~InputHandler()
{
    // TODO Auto-generated destructor stub
}

int InputHandler::open( void* )
{
    return -1;
}

} /* namespace ex_acceptor_connector */
