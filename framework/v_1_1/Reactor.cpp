/*
 * Reactor.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#include "../v_1_1/Reactor.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#include "../v_1_1/EventHandler.hpp"

namespace v_1_1
{

using namespace std;

Reactor *Reactor::mInstance = 0;

Reactor::Reactor()
{

}

Reactor::~Reactor()
{
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
    cout << "Reactor::"
         << __FUNCTION__
         << ":"
         << endl;

    int result = -1;
    fd_set readfds;

    while ( true )
    {
        // Clear the socket set
        FD_ZERO( &readfds );

        // Add server socket to set
        int maxFd = 0;

        for ( const auto &itHandler : mEventHandlerRepository )
        {
            int handle = itHandler.second.evHandler->getHandle();
            FD_SET( itHandler.second.evHandler->getHandle(), &readfds );

            if ( maxFd < handle )
            {
                maxFd = handle;
            }

        }

        // Wait for an activity on one of the sockets
        cout << "Reactor::"
             << __FUNCTION__
             << ": select(), maxFd="
             << maxFd
             << endl;

        int activity = select( maxFd + 1, &readfds, nullptr, nullptr, nullptr );

        if ( (activity < 0) && (errno != EINTR) )
        {
            std::cerr << "select error"
                      << std::endl;
        }else
        {
            cout << "Reactor::"
                 << __FUNCTION__
                 << ": select, activity="
                 << activity
                 << endl;
        }

        for ( const auto &itHandler : mEventHandlerRepository )
        {
            if ( FD_ISSET( itHandler.second.evHandler->getHandle(), &readfds ) )
            {
                itHandler.second.evHandler->handleInput( itHandler.second.evHandler->getHandle() );
            }

        }

        cleanUpRemovedHandler();

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

    if ( mEventHandlerRepository.find( event_handler->getHandle() )
         == mEventHandlerRepository.end() )
    {
        EvHandlerInfo evHandlerInfo;
        evHandlerInfo.valid = true;
        evHandlerInfo.evHandler = event_handler;
        evHandlerInfo.mask = mask;

        mEventHandlerRepository[event_handler->getHandle()] = evHandlerInfo;

        cout << "Reactor::"
             << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << endl;
    }else
    {
        cout << "Reactor::"
             << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << " already exist"
             << endl;
    }

    return result;
}

int Reactor::removeHandler( EventHandler *event_handler )
{
    if ( event_handler == nullptr )
    {
        return -1;
    }

    int result = 0;

    if ( mEventHandlerRepository.find( event_handler->getHandle() )
         == mEventHandlerRepository.end() )
    {

        cout << "Reactor::"
             << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << "not exist"
             << endl;

        result = -1;
    }else
    {
        mEventHandlerRepository[event_handler->getHandle()].valid = false;

        cout << "Reactor::"
             << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << " set to removed"
             << endl;
    }

    return result;
}

void Reactor::cleanUpRemovedHandler()
{

    for ( auto itHandler = mEventHandlerRepository.begin();
                    itHandler != mEventHandlerRepository.end(); )
    {
        if ( itHandler->second.valid == false )
        {
            delete itHandler->second.evHandler;
            itHandler = mEventHandlerRepository.erase( itHandler );
        }else
        {
            ++itHandler;
        }
    }

    cout << "Reactor::"
         << __FUNCTION__
         << ": Number of registered client = "
         << mEventHandlerRepository.size()
         << endl;

}
}/* namespace v_1_1 */
