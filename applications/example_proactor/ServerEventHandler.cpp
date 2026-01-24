/*
 * ServerEventHandler.cpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ServerEventHandler.hpp"
#include "Acceptor.hpp"

using namespace std;

namespace example_proactor
{

ServerEventHandler::ServerEventHandler( Acceptor &owner )
    : mOwner( &owner ),
      mMessageRead( 1024 ),
      mMessageWrite( 0 )

{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << endl;
}

ServerEventHandler::~ServerEventHandler()
{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << endl;

    close( handle() );
}

void ServerEventHandler::open( int new_handle )
{
    cout << "ServerEventHandler::"
         << __FUNCTION__
         << ": "
         << endl;

    mReader.open( *this, new_handle, 0, proactor() );
    mWriter.open( *this, new_handle, 0, proactor() );

    mReader.read( mMessageRead, mMessageRead.size() );
}

void ServerEventHandler::handleReadStream( const Proactor_1_0::AsynchReadStreamResult &result )
{
    if ( result.success() != true || result.bytes_transferred() == 0 )
    {
        delete this;
    }
    else if ( result.bytes_transferred() > 0 )
    {
        string messageReceived( result.message().begin(), result.message().begin() + result.bytes_transferred() );
        cout << "ServerEventHandler::"
             << __FUNCTION__
             << ": "
             << "received="
             << messageReceived
             << endl;

        string messageToSend = "Echo - " + string( messageReceived );
        mMessageWrite.assign( messageToSend.begin(), messageToSend.end() );
        mWriter.write( mMessageWrite, mMessageWrite.size() );

        cout << "Replied message: "
             << messageToSend
             << endl;

        mReader.read( mMessageRead, mMessageRead.size() );
    }
}

void ServerEventHandler::handleWriteStream( const Proactor_1_0::AsynchWriteStreamResult &result )
{
    if ( result.success() != true || result.bytes_transferred() == 0 )
    {
        cout << "ServerEventHandler::"
             << __FUNCTION__
             << ": "
             << "fail to send"
             << endl;
    }
    else if ( result.bytes_transferred() > 0 )
    {
        string messageReceived( result.message().begin(), result.message().begin() + result.bytes_transferred() );
        cout << "ServerEventHandler::"
             << __FUNCTION__
             << ": "
             << "sent="
             << messageReceived
             << endl;
    }
}
} /* namespace example_proactor */
