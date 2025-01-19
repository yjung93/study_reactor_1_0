/*
 * Acceptor.cpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#include <iostream>

#include "Acceptor.hpp"

namespace v_1_1
{

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::Acceptor( v_1_1::Reactor *reactor ) :
                EventHandler( reactor )
{
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::~Acceptor()
{
    // TODO Auto-generated destructor stub
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::open( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor )
{
//  ACE_TRACE ("ACE_Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::open");
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
    std::cout << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::close"
              << std::endl;

    return this->handleClose();
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleClose()
{

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleInput( int fd )
{
    std::cout << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleInput"
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
    std::cout << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::makeSvcHandler"
              << std::endl;

    if ( svcHandler == nullptr )
    {
        svcHandler = new SVC_HANDLER;
        svcHandler->setReactor( this->getReactor() );
    }else
    {
        std::cout << __FUNCTION__
                  << "svcHandler is not a null pointer, skip create svcHandler"
                  << std::endl;
    }

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler( SVC_HANDLER *svcHandler )
{
    std::cout << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler"
              << std::endl;

    // TBD:
    if ( this->acceptor().accept( svcHandler->getHandle(), // stream
                                  0, // remote address
                                  0 )
         == -1 )
    {
        // Close down handler to avoid memory leaks.
//        svcHandler->close( CLOSE_DURING_NEW_CONNECTION );

        return -1;
    }else
    {
        return 0;

    }

}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::activateSvcHandler( SVC_HANDLER *svcHandler )
{

    std::cout << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler"
              << std::endl;

    int result = 0;

    if ( result == 0 && svcHandler->open( (void*) this ) == -1 )
        result = -1;

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
    std::cout << __FUNCTION__
              << std::endl;
    return const_cast<PEER_ACCEPTOR&>( this->mPeerAcceptor );
}
} /* namespace v_1_1 */
