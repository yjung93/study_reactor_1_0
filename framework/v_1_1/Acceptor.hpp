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

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::Acceptor( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor, int flags ) :
                EventHandler( reactor )
{
    open( localAddr, reactor, flags );
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::Acceptor( Reactor *reactor, int flags ) :
                EventHandler( reactor )
{
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::~Acceptor()
{
    // TODO Auto-generated destructor stub
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::open( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor, int flags )
{
    this->mPeerAcceptorAddr = localAddr;

    // Must supply a valid Reactor to Acceptor::open()...

    if ( reactor == 0 )
    {
        return -1;
    }

    // Open the underlying PEER_ACCEPTOR.
    if ( this->mPeerAcceptor.open( mPeerAcceptorAddr ) == -1 )
        return -1;

    int const result = reactor->registerHandler( this,
                                                 EventHandler::ACCEPT_MASK );
    return result;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::close()
{
    std::cout << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::close" << std::endl;

    return this->handleClose();
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleClose( int handle )
{

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleInput( int fd )
{
    std::cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleInput"
    << std::endl;

    SVC_HANDLER *svcHandler = 0;

    makeSvcHandler( svcHandler );

    acceptSvcHandler( svcHandler );

    activateSvcHandler( svcHandler );

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::makeSvcHandler( SVC_HANDLER *&svcHandler )
{
    std::cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::makeSvcHandler"
    << std::endl;

    if ( svcHandler == nullptr )
    {
        svcHandler = new SVC_HANDLER;
        svcHandler->setReactor( this->getReactor() );
    }else
    {
        std::cout
        << __FUNCTION__
        << "svcHandler is not a null pointer, skip create svcHandler"
        << std::endl;
    }

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler( SVC_HANDLER *svcHandler )
{
    std::cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler"
    << std::endl;

    // TBD:
    if ( this->acceptor().accept( svcHandler->getHandle() ) == -1 )
    {
        // Close down handler to avoid memory leaks.
//        svcHandler->close( CLOSE_DURING_NEW_CONNECTION );

        return -1;
    }
    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::activateSvcHandler( SVC_HANDLER *svcHandler )
{

    std::cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler"
    << std::endl;

    int result = 0;

    if ( (result == 0) && (svcHandler->open( (void*) this ) == -1) )
    {
        result = -1;
    }

    if ( result == -1 )
    {
        // The connection was already made; so this close is a "normal" close
        // operation.
//        svcHandler->close( NORMAL_CLOSE_OPERATION );
    }

    return result;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
PEER_ACCEPTOR& Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptor() const
{
    std::cout << __FUNCTION__ << std::endl;
    return const_cast<PEER_ACCEPTOR&>( this->mPeerAcceptor );
}

} /* namespace v_1_1 */

#endif /* FRAMEWORK_V_1_1_ACCEPTOR_HPP_ */
