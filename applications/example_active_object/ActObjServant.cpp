
#include "ActObjServant.hpp"
#include <iostream>
#include <sys/socket.h>
#include <chrono>
#include <thread>

using namespace std;

namespace ExActiveObject
{
ActObjServant::ActObjServant()
{
    cout << "ActObjServant::"
         << __FUNCTION__
         << endl;
}

string ActObjServant::RequestGetReturnMessage( const string &message )
{
    cout << "ActObjServant::"
         << __FUNCTION__ << ": "
         << " message= "
         << message
         << endl;

    string result = "Echo - " + message;

    this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

    cout << "ActObjServant::"
         << __FUNCTION__ << ": "
         << "process completed, result= "
         << result
         << endl;

    return result;
}
} // namespace ExActiveObject
