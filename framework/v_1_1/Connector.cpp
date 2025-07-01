/*
 * Connector.cpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */
#ifndef FRAMEWORK_V_1_1_CONNECTOR_CPP_
#define FRAMEWORK_V_1_1_CONNECTOR_CPP_

#include <arpa/inet.h>
#include <iostream>
#include <cerrno>

#include "Connector.hpp"

namespace v_1_1
{
template<typename SVC_HANDLER, typename PEER_CONNECTOR>
Connector<SVC_HANDLER, PEER_CONNECTOR>::Connector( Reactor *reactor, int flags ) :
                EventHandler( reactor )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    this->open( reactor, flags );
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
Connector<SVC_HANDLER, PEER_CONNECTOR>::~Connector()
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;
}
template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::open( Reactor *reactor, int flags )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    this->setReactor( reactor );
    this->mFlags = flags;
    return 0;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
bool Connector<SVC_HANDLER, PEER_CONNECTOR>::close( SVC_HANDLER *&sh )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    return true;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
void Connector<SVC_HANDLER, PEER_CONNECTOR>::setReactor( Reactor *reactor )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;
    mReactor = reactor;
}
template<typename SVC_HANDLER, typename PEER_CONNECTOR>
Reactor* Connector<SVC_HANDLER, PEER_CONNECTOR>::getReactor() const
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;
    return mReactor;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::connect( SVC_HANDLER *&svcHandler, const typename PEER_CONNECTOR::PEER_ADDR &remoteAddr, int flags )
{
    int result = 0;

    result = makeSvcHandler( svcHandler );

    if ( result != -1 )
    {
        result = connectSvcHandler( svcHandler, remoteAddr, flags );
    }

    if ( result != -1 )
    {
        result = activateSvcHandler( svcHandler );
    }

    if ( result == -1 )
    {
        if ( errno == EINPROGRESS || errno == EWOULDBLOCK )
        {
            cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
                 << __FUNCTION__
                 << ": "
                 << "errno="
                 << ((errno == EINPROGRESS) ? "EINPROGRESS" : "EWOULDBLOCK")
                 << endl;

            nonblockingConnect( svcHandler );
        }
    }
    return result;
}
template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::handleInput( int fd )
{
    return 0;
}
template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::handleClose( int handle )
{
    return 0;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::makeSvcHandler( SVC_HANDLER *&svcHandler )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    if ( svcHandler == nullptr )
    {
        svcHandler = new SVC_HANDLER;
        svcHandler->setReactor( this->getReactor() );
    }else
    {
        cout << __FUNCTION__
             << "svcHandler is not a null pointer, skip create svcHandler"
             << endl;
    }

    return 0;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::connectSvcHandler( SVC_HANDLER *svcHandler, const typename PEER_CONNECTOR::PEER_ADDR remoteAddr, int flags )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << "flag=0x"
         << std::hex
         << flags
         << endl;

    int result = 0;

    if ( svcHandler == nullptr )
    {
        result = -1;
    }

    if ( result != -1 )
    {
        result = mConnector.connect( svcHandler->peer(), remoteAddr, 0, flags );
    }

    return result;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::activateSvcHandler( SVC_HANDLER *svcHandler )
{

    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    int result = 0;
    if ( svcHandler == nullptr )
    {
        result = -1;
    }

    if ( result != -1 )
    {
        if ( svcHandler->open( (void*) this ) == -1 )
        {
            result = -1;
        }
    }

    if ( result == -1 )
    {
        svcHandler->close();
    }

    return result;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
int Connector<SVC_HANDLER, PEER_CONNECTOR>::nonblockingConnect( SVC_HANDLER *svcHandler )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    int result = -1;
    NBCH *nbch = 0;
    if ( svcHandler != nullptr )
    {
        nbch = new NBCH( *this, svcHandler );
        result = getReactor()->registerHandler( nbch,
                                                EventHandler::CONNECT_MASK );
    }

    // TBD : register timer, once it is available

    return result;
}

template<typename SVC_HANDLER, typename PEER_CONNECTOR>
void Connector<SVC_HANDLER, PEER_CONNECTOR>::initializeSvcHandler( int handle, SVC_HANDLER *svc_handler )
{
    cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
         << __FUNCTION__
         << ": "
         << endl;

    bool result = true;

    if ( svc_handler == nullptr )
    {
        result = false;
    }

    if ( result == true )
    {
        svc_handler->setHandle( handle );

        typename PEER_CONNECTOR::PEER_ADDR raddr;

        // Check to see if we're connected.
        if ( svc_handler->peer().getRemoteAddr( raddr ) != -1 )
        {
            activateSvcHandler( svc_handler );
        }else // Somethings gone wrong, so close down...
        {
            svc_handler->close();
        }
    }

}

template<typename SVC_HANDLER>
NonBlockingConnectHandler<SVC_HANDLER>::NonBlockingConnectHandler( ConnectorBase<
                                                                                   SVC_HANDLER> &connector, SVC_HANDLER *sh ) :
                mConnector( connector ),
                mSvcHandler( sh )
{
    if ( mSvcHandler != nullptr )
    {
        setHandle( mSvcHandler->getHandle() );
    }
}

template<typename SVC_HANDLER>
NonBlockingConnectHandler<SVC_HANDLER>::~NonBlockingConnectHandler()
{

}
template<typename SVC_HANDLER>
int NonBlockingConnectHandler<SVC_HANDLER>::handleOutput( int handle )
{
    // Called when a connection is establishment asynchronous.
    cout << "NonBlockingConnectHandler<SVC_HANDLER>::"
         << __FUNCTION__
         << ": "
         << endl;

    // Grab the connector ref before smashing ourselves in close().
    ConnectorBase<SVC_HANDLER> &connector = this->mConnector;
    SVC_HANDLER *svc_handler = 0;
    int const retval = this->close( svc_handler ) ? 0 : -1;

    if ( svc_handler != 0 )
    {
        connector.initializeSvcHandler( handle, svc_handler );
    }

    return retval;
}

template<typename SVC_HANDLER>
int NonBlockingConnectHandler<SVC_HANDLER>::handleInput( int handle )
{
    cout << "NonBlockingConnectHandler<SVC_HANDLER>::"
         << __FUNCTION__
         << ": "
         << endl;

    return 0;
}

template<typename SVC_HANDLER>
int NonBlockingConnectHandler<SVC_HANDLER>::handleClose( int handle )
{
    cout << "NonBlockingConnectHandler<SVC_HANDLER>::"
         << __FUNCTION__
         << ": "
         << endl;

    return 0;
}

template<typename SVC_HANDLER>
int NonBlockingConnectHandler<SVC_HANDLER>::handleException( int handle )
{
    cout << "NonBlockingConnectHandler<SVC_HANDLER>::"
         << __FUNCTION__
         << ": "
         << endl;

    return 0;
}

template<typename SVC_HANDLER>
SVC_HANDLER* NonBlockingConnectHandler<SVC_HANDLER>::svcHandler()
{
    cout << "NonBlockingConnectHandler<SVC_HANDLER>::"
         << __FUNCTION__
         << ": "
         << endl;

    return mSvcHandler;
}

template<typename SVC_HANDLER>
bool NonBlockingConnectHandler<SVC_HANDLER>::close( SVC_HANDLER *&sh )
{
    bool result = true;

    // Make sure that we haven't already initialized the Svc_Handler.
    if ( this->mSvcHandler == nullptr )
    {
        result = false;
    }

    if ( result == true )
    {
        // Exclusive access to the Reactor.
//        TBD , ACE_GUARD_RETURN( ACE_Lock, ace_mon, this->reactor()->lock(), 0 );

// Double check.
        if ( this->mSvcHandler == nullptr )
        {
            result = false;
        }

        if ( result == true )
        {
            sh = this->mSvcHandler;
            this->mSvcHandler = 0;

            // Remove from Reactor.
            if ( this->getReactor()->removeHandler( sh, ALL_EVENTS_MASK )
                 == -1 )
            {

                result = false;
            }
            this->mSvcHandler = 0;
        }
    }
    return result;
}

} /* namespace v_1_1 */

#endif /* FRAMEWORK_V_1_1_CONNECTOR_CPP_ */
