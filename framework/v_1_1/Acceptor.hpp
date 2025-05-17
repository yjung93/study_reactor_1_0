/*
 * Acceptor.hpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_ACCEPTOR_HPP_
#define FRAMEWORK_V_1_1_ACCEPTOR_HPP_

#include <arpa/inet.h>
#include <iostream>

#include "framework/v_1_1/EventHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"

using namespace std;

namespace v_1_1
{
template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
class Acceptor: public EventHandler

{
public:

    Acceptor( Reactor *reactor = 0, int flags = 0 );
    Acceptor( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor =
                    0, int flags = 0 );
    virtual ~Acceptor();

    virtual int open( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor =
                    Reactor::getInstance(), int flags = 0 );
    virtual int close();

    virtual PEER_ACCEPTOR& acceptor() const;

protected:

    virtual int makeSvcHandler( SVC_HANDLER *&svcHandler );
    virtual int acceptSvcHandler( SVC_HANDLER *svcHandler );
    virtual int activateSvcHandler( SVC_HANDLER *svcHandler );

    int handleInput( int fd = INVALID_HANDLE ) override;
    int handleClose( int handle = INVALID_HANDLE ) override;

    // Concrete factory for accepting connections from clients...
    PEER_ACCEPTOR mPeerAcceptor;

    // Needed to reopen the socket if {accept} fails.
    typename PEER_ACCEPTOR::PEER_ADDR mPeerAcceptorAddr;

};



} /* namespace v_1_1 */

// for splitting the template class definition into .cpp
#include "Acceptor.cpp"

#endif /* FRAMEWORK_V_1_1_ACCEPTOR_HPP_ */
