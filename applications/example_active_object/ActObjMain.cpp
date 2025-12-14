
#include "applications/example_active_object/ActObjMain.hpp"
#include "applications/example_active_object/ActObjAcceptor.hpp"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

namespace ExActiveObject
{

ActObjMain::ActObjMain( Reactor_1_0::Reactor *reactor, ActObjAcceptor &owner )
    : EventHandler( reactor ),
      mOwner( &owner )
{
    cout << "ActObjMain::"
         << __FUNCTION__
         << endl;
}

ActObjMain::~ActObjMain()
{
    cout << "ActObjMain::"
         << __FUNCTION__
         << endl;
}

void ActObjMain::open()
{
    cout << "ActObjMain::"
         << __FUNCTION__
         << endl;
    getReactor()->registerHandler( this, EventHandler::READ_MASK );

    // Initialize ActObjClient
    mActObjClient.reset( new ActObjClient( getHandle() ) );
    mActObjClient->open();
}

int ActObjMain::handleInput( int fd )
{
    cout << "ActObjMain::"
         << __FUNCTION__
         << endl;

    const int bufferSize = 1024;

    char buffer[bufferSize] = { 0 };

    int valread = read( fd, buffer, bufferSize );
    if ( valread <= 0 )
    {
        if ( valread == 0 )
        {
            cout << "Client disconnected, socket FD: "
                 << fd
                 << endl;
        }
        else
        {
            perror( "read failed" );
        }

        close( fd );
        getReactor()->removeHandler( this, ALL_EVENTS_MASK );
        if ( mOwner != nullptr )
        {
            mOwner->removeConnection( fd );
        }
        // return here immediately to avoid further processing since this object is likely destroyed.
        return 0;
    }

    cout << "Received message: "
         << buffer
         << endl;

    mActObjClient->putQ( string( buffer, static_cast<size_t>( valread ) ) );

    return 0;
}

} /* namespace  ExActiveObject */
