/*
 * Reactor.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#include "Reactor.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "EventHandler.hpp"

namespace v_1_1
{

using namespace std;

Reactor *Reactor::mInstance = 0;

Reactor::Reactor()
{
    if ( pipe( mWakeupPipe ) < 0 )
    {
        perror( "pipe creation failed" );
        exit( EXIT_FAILURE );
    }

    // Set read end non-blocking
    fcntl( mWakeupPipe[0], F_SETFL, O_NONBLOCK );
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
    fd_set writefds;

    while ( true )
    {

        // Clear the socket set
        FD_ZERO( &readfds );
        FD_ZERO( &writefds );

        // Add server socket to set
        int maxFd = 0;

        {
            const std::lock_guard<std::recursive_mutex> lock( mMutexRepoository );

            for ( const auto &itHandler : mEventHandlerRepository )
            {
                int handle = itHandler.second.evHandler->getHandle();

                if ( ((itHandler.second.mask & EventHandler::READ_MASK) != 0)
                     || ((itHandler.second.mask & EventHandler::ACCEPT_MASK)
                         != 0) )
                {
                    FD_SET( itHandler.second.evHandler->getHandle(), &readfds );

                }else if ( (itHandler.second.mask & EventHandler::CONNECT_MASK)
                           != 0 )
                {
                    FD_SET( itHandler.second.evHandler->getHandle(),
                            &writefds );
                }

                if ( maxFd < handle )
                {
                    maxFd = handle;
                }

            }

            // Add wake-up pipe read end
            FD_SET( mWakeupPipe[0], &readfds );
            if ( mWakeupPipe[0] > maxFd )
            {
                maxFd = mWakeupPipe[0];
            }
        }
        // Wait for an activity on one of the sockets
        cout << "Reactor::"
             << __FUNCTION__
             << ": select(), maxFd="
             << maxFd
             << endl;

        int activity = select( maxFd + 1,
                               &readfds,
                               &writefds,
                               nullptr,
                               nullptr );

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

        // Handle wakeup
        if ( FD_ISSET( mWakeupPipe[0], &readfds ) )
        {
            char buf[64];
            ::read( mWakeupPipe[0], buf, sizeof(buf) ); // Drain pipe

            cout << "Reactor::"
                 << __FUNCTION__
                 << ": woke up from pipe"
                 << endl;
        }

        vector<EvHandlerInfo> readhandles;
        vector<EvHandlerInfo> writehandles;

        {
            const std::lock_guard<std::recursive_mutex> lock( mMutexRepoository );

            for ( const auto &itHandler : mEventHandlerRepository )
            {
                if ( FD_ISSET( itHandler.second.evHandler->getHandle(),
                               &readfds ) )
                {
                    readhandles.push_back( itHandler.second );

                }

                if ( FD_ISSET( itHandler.second.evHandler->getHandle(),
                               &writefds ) )
                {
                    writehandles.push_back( itHandler.second );
                }

            }
        }

        for ( const auto &itRd : readhandles )
        {
            itRd.evHandler->handleInput( itRd.evHandler->getHandle() );
        }

        for ( const auto &irRw : writehandles )
        {
            irRw.evHandler->handleOutput( irRw.evHandler->getHandle() );
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
    const std::lock_guard<std::recursive_mutex> lock( mMutexRepoository );

    int result = 0;

    if ( event_handler == nullptr )
    {
        result = -1;
    }

    if ( result != -1 )
    {
        event_handler->setReactor( this );

        if ( mEventHandlerRepository.find( event_handler->getHandle() )
             == mEventHandlerRepository.end() )
        {
            EvHandlerInfo evHandlerInfo;
            evHandlerInfo.evHandler = event_handler;
            evHandlerInfo.mask = mask;

            mEventHandlerRepository[event_handler->getHandle()] = evHandlerInfo;

            cout << "Reactor::"
                 << __FUNCTION__
                 << ": handle="
                 << event_handler->getHandle()
                 << ", mask=0x"
                 << hex
                 << mask
                 << dec
                 << " add information"
                 << endl;
        }else
        {
            mEventHandlerRepository[event_handler->getHandle()].mask |= mask;

            cout << "Reactor::"
                 << __FUNCTION__
                 << ": handle="
                 << event_handler->getHandle()
                 << ", mask=0x"
                 << hex
                 << mask
                 << dec
                 << " already exist, update information"
                 << endl;
        }

        notifySelectLoop();
    }

    std::stringstream ss;
    ss << "Reactor::"
       << __FUNCTION__;

    dbgRepository( ss.str() );

    return result;
}

int Reactor::removeHandler( EventHandler *event_handler, ReactorMask mask )
{
    const std::lock_guard<std::recursive_mutex> lock( mMutexRepoository );

    if ( event_handler == nullptr )
    {
        return -1;
    }

    cout << "Reactor::"
         << __FUNCTION__
         << ":"
         << "handle="
         << event_handler->getHandle()
         << " mask=0x"
         << std::hex
         << mask
         << std::dec
         << endl;

    int result = 0;

    if ( mEventHandlerRepository.find( event_handler->getHandle() )
         == mEventHandlerRepository.end() )
    {

        cout << "Reactor::"
             << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << "does not exist"
             << endl;

        result = -1;
    }else
    {
        EvHandlerInfo &evHandler =
                        mEventHandlerRepository[event_handler->getHandle()];

        evHandler.mask &= ~mask;
        if ( evHandler.mask == 0u )
        {
            mEventHandlerRepository.erase( event_handler->getHandle() );
        }

        cout << "Reactor::"
             << __FUNCTION__
             << ": handle="
             << event_handler->getHandle()
             << " is removed"
             << endl;

        notifySelectLoop();
    }

    std::stringstream ss;
    ss << "Reactor::"
       << __FUNCTION__;
    dbgRepository( ss.str() );

    return result;
}

void Reactor::notifySelectLoop()
{
    // Notify the select loop to rebuild FD sets
    ::write( mWakeupPipe[1], "w", 1 );
}
void Reactor::dbgRepository( string title )
{
    const std::lock_guard<std::recursive_mutex> lock( mMutexRepoository );

    cout << title
         << ": mEventHandlerRepository size="
         << mEventHandlerRepository.size()
         << endl;

    for ( const auto &itHandler : mEventHandlerRepository )
    {
        cout << title
             << ": ["
             << itHandler.first
             << "]"
             << " handle="
             << itHandler.second.evHandler->getHandle()
             << " mask=0x"
             << std::hex
             << itHandler.second.mask
             << std::dec
             << endl;

    }
}
}/* namespace v_1_1 */
