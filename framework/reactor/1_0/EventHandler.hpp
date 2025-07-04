/*
 * EventHandler.hpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#ifndef REACTOR_1_0_EVENTHANDLER_HPP_
#define REACTOR_1_0_EVENTHANDLER_HPP_

#include <cstdio>

namespace Reactor_1_0
{

// Forward declaration.
class Reactor;

# define INVALID_HANDLE -1

typedef unsigned long ReactorMask;

class EventHandler
{
public:

    enum
    {
        LO_PRIORITY = 0,
        HI_PRIORITY = 10,
        NULL_MASK = 0,
        READ_MASK = (1 << 0),
        WRITE_MASK = (1 << 1),
        EXCEPT_MASK = (1 << 2),
        ACCEPT_MASK = (1 << 3),
        CONNECT_MASK = (1 << 4),
        TIMER_MASK = (1 << 5),
        QOS_MASK = (1 << 6),
        GROUP_QOS_MASK = (1 << 7),
        SIGNAL_MASK = (1 << 8),
        ALL_EVENTS_MASK = READ_MASK
                          | WRITE_MASK
                          | EXCEPT_MASK
                          | ACCEPT_MASK
                          | CONNECT_MASK
                          | TIMER_MASK
                          | QOS_MASK
                          | GROUP_QOS_MASK
                          | SIGNAL_MASK,
        RWE_MASK = READ_MASK | WRITE_MASK | EXCEPT_MASK,
        DONT_CALL = (1 << 9)
    };

    EventHandler( Reactor *reactor = nullptr );
    virtual ~EventHandler();

    virtual int handleInput( int fd = INVALID_HANDLE );
    virtual int handleOutput( int fd = INVALID_HANDLE );
    virtual int handleException( int fd = INVALID_HANDLE );
    virtual int handleClose( int handle );
    virtual int handleSignal( int signun );

    Reactor* getReactor() const;
    void setReactor( Reactor *reactor );

    virtual int getHandle() const;
    void setHandle( int fd );

protected:

private:
    Reactor *mReactor;
    int mFd;

};

} /* namespace Reactor_1_0 */

#endif /* REACTOR_1_0_EVENTHANDLER_HPP_ */
