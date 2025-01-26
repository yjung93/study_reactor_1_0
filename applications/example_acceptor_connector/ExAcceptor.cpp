/*
 * ExAcceptor.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include "ExAcceptor.hpp"

namespace ex_acceptor_connector
{

ExAcceptor::ExAcceptor( v_1_1::Reactor *reactor ) :
                PARENT( reactor, 0 )

{

}

ExAcceptor::~ExAcceptor()
{
}

} /* namespace ex_acceptor_connector */

