
#include "applications/example_active_object/ActObjAcceptor.hpp"
#include <iostream>
#include <thread>

#include "framework/reactor/1_0/Reactor.hpp"

using namespace std;

void serverThreadFunction( Reactor_1_0::Reactor *reactor )
{
    cout << "serverThreadFuncion"
         << endl;

    reactor->runReactorEventLoop();
}

int main( int argc, char **argv )
{

    Reactor_1_0::Reactor *reactor = Reactor_1_0::Reactor::getInstance();

    ExActiveObject::ActObjAcceptor acceptor( reactor );

    std::thread serverThread( serverThreadFunction, reactor );

    // Wait for the thread to finish execution
    if ( serverThread.joinable() )
    {
        serverThread.join();
    }

    return 0;
}
