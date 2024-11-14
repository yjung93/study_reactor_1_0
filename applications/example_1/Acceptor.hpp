/*
 * Acceptor.hpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_ACCEPTOR_HPP_
#define APPLICATIONS_EXAMPLE_1_ACCEPTOR_HPP_

#include <arpa/inet.h>

#include "v_1_0/EventHandler.hpp"
#include "v_1_0/Reactor.hpp"

namespace example_1
{

class Acceptor: public v_1_0::EventHandler
{
public:
    Acceptor( v_1_0::Reactor *reactor = v_1_0::Reactor::getInstance() );
    virtual ~Acceptor();

    void open();
    int handleInput( int fd = INVALID_HANDLE ) override;

private:
    struct sockaddr_in mAddress;
};

} /* namespace example_1 */

#endif /* APPLICATIONS_EXAMPLE_1_ACCEPTOR_HPP_ */
