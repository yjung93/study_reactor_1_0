/*
 * main.cpp
 *
 *  Created on: Jan 22, 2024
 *      Author: yjung93
 */

#include <iostream>
#include <thread>

#include "v_1_0/Reactor.hpp"
#include "Server.hpp"
#include "Acceptor.hpp"

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
    example_1::Acceptor acceptor( &reactor );

    std::thread serverThread( serverThreadFuncion, &reactor );

    // Wait for the thread to finish execution
    if ( serverThread.joinable() )
    {
        serverThread.join();
    }

    return 0;
}
