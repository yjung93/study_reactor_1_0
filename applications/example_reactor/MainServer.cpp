/*
 * main.cpp
 *
 *  Created on: Jan 22, 2024
 *      Author: yjung93
 */

#include <applications/example_reactor/Acceptor.hpp>
#include <iostream>
#include <thread>

#include "framework/v_1_0/Reactor.hpp"

using namespace std;

void serverThreadFuncion( v_1_0::Reactor *reactor )
{
    cout << "serverThreadFuncion"
         << endl;

    reactor->runReactorEventLoop();
}

int main( int argc, char **argv )
{

    v_1_0::Reactor reactor;
    example_reactor::Acceptor acceptor( &reactor );

    std::thread serverThread( serverThreadFuncion, &reactor );

    // Wait for the thread to finish execution
    if ( serverThread.joinable() )
    {
        serverThread.join();
    }

    return 0;
}
