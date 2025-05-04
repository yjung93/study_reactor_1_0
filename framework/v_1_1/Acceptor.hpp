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

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::Acceptor( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor, int flags ) :
                EventHandler( reactor )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;
    open( localAddr, reactor, flags );
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::Acceptor( Reactor *reactor, int flags ) :
                EventHandler( reactor )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::~Acceptor()
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::open( const typename PEER_ACCEPTOR::PEER_ADDR &localAddr, Reactor *reactor, int flags )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;
    int result = 0;

    this->mPeerAcceptorAddr = localAddr;

    // Must supply a valid Reactor to Acceptor::open()...
    if ( result != -1 && reactor == 0 )
    {
        result = -1;
    }

    // Open the underlying PEER_ACCEPTOR.
    if ( result != -1 && this->mPeerAcceptor.open( mPeerAcceptorAddr ) == -1 )
    {
        result = -1;
    }

    if ( result != -1 )
    {
        setHandle( this->mPeerAcceptor.getHandle() );
        result = reactor->registerHandler( this, EventHandler::ACCEPT_MASK );
    }
    return result;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::close()
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;

    return this->handleClose();
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleClose( int handle )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;
    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::handleInput( int fd )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << " fd="
    << fd
    << endl;

    SVC_HANDLER *svcHandler = 0;

    makeSvcHandler( svcHandler );

    acceptSvcHandler( svcHandler );

    activateSvcHandler( svcHandler );

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::makeSvcHandler( SVC_HANDLER *&svcHandler )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;

    if ( svcHandler == nullptr )
    {
        svcHandler = new SVC_HANDLER;
        svcHandler->setReactor( this->getReactor() );
    }else
    {
        cout
        << __FUNCTION__
        << "svcHandler is not a null pointer, skip create svcHandler"
        << endl;
    }

    return 0;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler( SVC_HANDLER *svcHandler )
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;

    int result = 0;

    int svchandle = this->acceptor().accept( mPeerAcceptor.getHandle() );

    if ( svchandle == -1 )
    {
        // Close down handler to avoid memory leaks.

        cout
        << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler"
        << ": "
        << "fail to accept"
        << endl;

        svcHandler->close();
        result = -1;
    }

    if ( result != -1 )
    {
        cout
        << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptSvcHandler"
        << ": "
        << "svchandle = "
        << svchandle
        << endl;
        svcHandler->setHandle( svchandle );
    }
    return result;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
int Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::activateSvcHandler( SVC_HANDLER *svcHandler )
{

    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;

    int result = 0;

    if ( svcHandler->open( (void*) this ) == -1 )
    {
        result = -1;
    }

    if ( result == -1 )
    {
        // The connection was already made; so this close is a "normal" close
        svcHandler->close();
    }

    return result;
}

template<typename SVC_HANDLER, typename PEER_ACCEPTOR>
PEER_ACCEPTOR& Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::acceptor() const
{
    cout
    << "Acceptor<SVC_HANDLER, PEER_ACCEPTOR>::"
    << __FUNCTION__
    << ": "
    << endl;
    return const_cast<PEER_ACCEPTOR&>( this->mPeerAcceptor );
}

} /* namespace v_1_1 */

#endif /* FRAMEWORK_V_1_1_ACCEPTOR_HPP_ */
