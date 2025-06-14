/*
 * ExConnector.cpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#include "ExConnector.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

namespace ex_acceptor_connector
{

constexpr int PORT = 8080;

ExConnector::ExConnector( v_1_1::Reactor *reactor ) :
                PARENT( reactor, 0 )

{


}

ExConnector::~ExConnector()
{
}

} /* namespace ex_acceptor_connector */

