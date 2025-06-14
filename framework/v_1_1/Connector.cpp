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
int Connector<SVC_HANDLER, PEER_CONNECTOR>::connect( SVC_HANDLER *&svcHandler, const typename PEER_CONNECTOR::PEER_ADDR &remoteAddr )
{
    int result = 0;

    result = makeSvcHandler( svcHandler );

    if ( result != -1 )
    {
        result = connectSvcHandler( svcHandler, remoteAddr );
    }

    if ( result != -1 )
    {
        result = activateSvcHandler( svcHandler );
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
int Connector<SVC_HANDLER, PEER_CONNECTOR>::connectSvcHandler( SVC_HANDLER *svcHandler, const typename PEER_CONNECTOR::PEER_ADDR remoteAddr )
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
        result = mConnector.connect( svcHandler->peer(), remoteAddr );

        if ( result == -1 )
        {
            // Close down handler to avoid memory leaks.

            cout << "Connector<SVC_HANDLER, PEER_CONNECTOR>::"
                 << __FUNCTION__
                 << ": "
                 << "fail to connect"
                 << endl;

            svcHandler->close();
        }
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

} /* namespace v_1_1 */

#endif /* FRAMEWORK_V_1_1_CONNECTOR_CPP_ */
