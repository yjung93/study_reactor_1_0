
#include "ActObjScheduler.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;

namespace ExActiveObject
{

ActObjScheduler::ActObjScheduler(  )
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;
}
ActObjScheduler::~ActObjScheduler()
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;
}

int ActObjScheduler::open( void *args )
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;

    return activate();
}
int ActObjScheduler::svc()
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;

    string message;
    while ( getQ( message ) == 0 )
    {
        processMessage( message );
    }

    return 0;
}

void ActObjScheduler::processMessage( const std::string &message )
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;

    string messageToSend = "Echo - " + message;
    // send( mSocketFd, messageToSend.c_str(), messageToSend.size(), 0 );
}

}//namespace ExActiveObject
