
#include "ActObjServant.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;

namespace ExActiveObject
{
ActObjServant::ActObjServant()
{
    cout << "ActObjServant::"
         << __FUNCTION__
         << endl;
}
ActObjServant::~ActObjServant()
{
    cout << "ActObjServant::"
         << __FUNCTION__
         << endl;
}

int ActObjServant::open( void *args )
{
    cout << "ActObjServant::"
         << __FUNCTION__
         << endl;

    return activate();
}
int ActObjServant::svc()
{
    cout << "ActObjServant::"
         << __FUNCTION__
         << endl;

    string message;
    while ( getQ( message ) == 0 )
    {
        processMessage( message );
    }

    return 0;
}

void ActObjServant::processMessage( const std::string &message )
{
    cout << "ActObjServant::"
         << __FUNCTION__
         << endl;

    string messageToSend = "Echo - " + message;
    // send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
}

} // namespace ExActiveObject
