/*
 * main.cpp
 *
 *  Created on: Jan 22, 2024
 *      Author: yjung93
 */

#include "applications/example_reactor/Acceptor.hpp"
#include <iostream>
#include <thread>

#include "framework/reactor/1_0/Reactor.hpp"

using namespace std;

void serverThreadFuncion( Reactor_1_0::Reactor *reactor )
{
    cout << "serverThreadFuncion"
         << endl;

    reactor->runReactorEventLoop();
}

int main( int argc, char **argv )
{

    Reactor_1_0::Reactor *reactor = Reactor_1_0::Reactor::getInstance();

    example_reactor::Acceptor acceptor( reactor );

    std::thread serverThread( serverThreadFuncion, reactor );

    // Wait for the thread to finish execution
    if ( serverThread.joinable() )
    {
        serverThread.join();
    }

    return 0;
}
