/*
 * Reactor.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include "Reactor.hpp"
#include "EventHandler.hpp"

namespace v_1_0
{

using namespace std;

Reactor *Reactor::mInstance = 0;

Reactor::Reactor()
{
    // TODO Auto-generated constructor stub

}

Reactor::~Reactor()
{
    // TODO Auto-generated destructor stub
}

Reactor* Reactor::getInstance()
{

    if ( Reactor::mInstance == nullptr )
    {

        Reactor::mInstance = new Reactor();
    }

    return Reactor::mInstance;
}

void Reactor::closeSingleton()
{

    delete Reactor::mInstance;
    Reactor::mInstance = 0;
}

int Reactor::runReactorEventLoop()
{
    printf( "Reactor::%s\n", __FUNCTION__ );

    while ( 1 )
    {
        int result = handleEvents();

        if ( result == -1 )
        {
            if ( deactivated() )
            {
                result = 0;
            }
            return result;
        }else if ( result == 0 )
        {
            return 0;
        }
        // Else there were some events dispatched; go around again
    }

    return 0;
}

int Reactor::handleEvents()
{
    int result = -1;
    fd_set readfds;

    while ( true )
    {
        // Clear the socket set
        FD_ZERO( &readfds );

        // Add server socket to set
        int maxFd = 0;

        for ( auto itHandler : mEventHandlerRepository )
        {
            int handle = itHandler.second.evHandler->getHandle();
            FD_SET( itHandler.second.evHandler->getHandle(), &readfds );

            if ( maxFd < handle )
            {
                maxFd = handle;
            }

            cout << __FUNCTION__
                 << ": before select"
                 << "handle="
                 << handle
                 << ", maxFd="
                 << maxFd
                 << endl;
        }

        // Wait for an activity on one of the sockets
        int activity = select( maxFd + 1, &readfds, nullptr, nullptr, nullptr );
        cout << __FUNCTION__
             << ": after select"
             << "activity="
             << activity
             << endl;

        if ( (activity < 0) && (errno != EINTR) )
        {
            std::cerr << "select error"
                      << std::endl;
        }

        for ( auto itHandler : mEventHandlerRepository )
        {
            if ( FD_ISSET( itHandler.second.evHandler->getHandle(), &readfds ) )
            {
                itHandler.second.evHandler->handleInput( itHandler.second.evHandler->getHandle() );
            }
        }

    }
    return result;
}

int Reactor::deactivated()
{
    int result = -1;

    return result;
}

int Reactor::registerHandler( EventHandler *event_handler, ReactorMask mask )
{
    if ( event_handler == nullptr )
    {
        return 0;
    }

    int result = 0;

    if ( mEventHandlerRepository.find( event_handler->getHandle() ) == mEventHandlerRepository.end() )
    {
        EvHandlerInfo evHandlerInfo;
        evHandlerInfo.evHandler = event_handler;
        evHandlerInfo.mask = mask;

        mEventHandlerRepository[event_handler->getHandle()] = evHandlerInfo;

        cout << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << endl;
    }

    return result;
}

} /* namespace v_1_0 */
