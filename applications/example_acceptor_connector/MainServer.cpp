/*
 * main.cpp
 *
 *  Created on: Jan 22, 2024
 *      Author: yjung93
 */

#include "applications/example_acceptor_connector/ExAcceptor.hpp"
#include <iostream>
#include <thread>

#include "framework/v_1_1/Reactor.hpp"

using namespace std;
using namespace ex_acceptor_connector;

void serverThreadFuncion( v_1_1::Reactor *reactor )
{
    cout << "serverThreadFuncion"
         << endl;

    reactor->runReactorEventLoop();
}

int main( int argc, char **argv )
{

    ExAcceptor acceptor( v_1_1::Reactor::getInstance() );

    std::thread serverThread( serverThreadFuncion,
                              v_1_1::Reactor::getInstance() );

    // Wait for the thread to finish execution
    if ( serverThread.joinable() )
    {
        serverThread.join();
    }

    v_1_1::Reactor::closeSingleton();
    return 0;
}
