/*
 * Reactor.hpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#ifndef V_1_0_REACTOR_HPP_
#define V_1_0_REACTOR_HPP_

#include <cstdio>
#include <unordered_map>

#include "EventHandler.hpp"

namespace v_2_0
{

class Reactor
{
public:

    struct EvHandlerInfo
    {
        bool valid = false;
        ReactorMask mask;
        EventHandler *evHandler;
    };

    typedef std::unordered_map<int, EvHandlerInfo> EventHandlerRepository;

    Reactor();
    virtual ~Reactor();
    static Reactor* getInstance();
    static void closeSingleton();
    int runReactorEventLoop();
    int handleEvents();
    int deactivated();
    int registerHandler( EventHandler *event_handler, ReactorMask mask );
    int removeHandler( EventHandler *event_handler );


protected:

    void cleanUpRemovedHandler();

    static Reactor *mInstance;
    EventHandlerRepository mEventHandlerRepository;

};

} /* namespace v_2_0 */

#endif /* V_1_0_REACTOR_HPP_ */
