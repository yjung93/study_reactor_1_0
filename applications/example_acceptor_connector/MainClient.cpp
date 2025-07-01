#include "ExConnector.hpp"
#include <iostream>
#include <thread>

#include "framework/v_1_1/Reactor.hpp"
#include "applications/example_acceptor_connector/Client.hpp"

using namespace std;
using namespace ex_acceptor_connector;

void clientThreadFuncion( v_1_1::Reactor *reactor )
{
    cout << "clientThreadFuncion"
         << endl;

    reactor->runReactorEventLoop();
}

int main()
{



    std::thread clientThread( clientThreadFuncion,
                              v_1_1::Reactor::getInstance() );

    Client client;
    client.initialize();

    bool loop = true;
    while ( loop )
    {
        std::string input;

        std::cout << "Enter Message : ";
        std::getline( std::cin, input );

        if ( input.length() > 0 )
        {

            if ( input == "exit" )
            {
                loop = false;
            }else
            {
                client.sendMessage( input );
            }
        }

    }
    client.finish();

    // Wait for the thread to finish execution
    if ( clientThread.joinable() )
    {
        clientThread.join();
    }

    v_1_1::Reactor::closeSingleton();
    return 0;
}

