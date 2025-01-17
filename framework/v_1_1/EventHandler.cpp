/*
 * EventHandler.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#include "../v_1_1/EventHandler.hpp"

namespace v_1_1
{

EventHandler::EventHandler( Reactor *reactor ) :
                mReactor( reactor )
{
    // TODO Auto-generated constructor stub

}

EventHandler::~EventHandler()
{
    // TODO Auto-generated destructor stub
}

int EventHandler::handleInput( int fd )
{
    printf( "EventHandler::%s\n", __FUNCTION__ );
    return -1;

}

int EventHandler::handleOutput( int fd )
{
    printf( "EventHandler::%s\n", __FUNCTION__ );
    return -1;

}

int EventHandler::handleException( int fd )
{
    printf( "EventHandler::%s\n", __FUNCTION__ );
    return -1;

}

int EventHandler::handleClose( int fd )
{
    printf( "EventHandler::%s\n", __FUNCTION__ );
    return -1;

}

int EventHandler::handleSignal( int signum )
{
    printf( "EventHandler::%s, signum:%d\n", __FUNCTION__, signum );
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

} /* namespace v_1_1 */
