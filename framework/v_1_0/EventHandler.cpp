/*
 * EventHandler.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#include "EventHandler.hpp"

namespace v_1_0
{

EventHandler::EventHandler( Reactor *reactor ) :
                mReactor( reactor )
{
}

EventHandler::~EventHandler()
{
}

int EventHandler::handleInput( int fd )
{
    printf( "EventHandler::%s\n", __FUNCTION__ );
    return -1;

}

Reactor* EventHandler::getReactor() const
{
    return mReactor;
}

int EventHandler::getHandle()
{
    return mFd;
}

void EventHandler::setHandle( int fd )
{
    mFd = fd;
}

} /* namespace v_1_0 */
