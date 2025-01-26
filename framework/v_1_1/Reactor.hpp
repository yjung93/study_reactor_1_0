/*
 * Reactor.hpp
 *
 *  Created on: Jan 12, 2024
 *      Author: yjung93
 */

#ifndef V_1_1_REACTOR_HPP_
#define V_1_1_REACTOR_HPP_

#include <cstdio>
#include <unordered_map>

#include "../v_1_1/EventHandler.hpp"

namespace v_1_1
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

private:
    Reactor();
    virtual ~Reactor();

};

} /* namespace v_1_1 */

#endif /* V_1_1_REACTOR_HPP_ */
