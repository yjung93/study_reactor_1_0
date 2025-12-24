
#include "ActObjScheduler.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;

namespace ExActiveObject
{

ActObjScheduler::ActObjScheduler()
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;
         
    activate();
}
ActObjScheduler::~ActObjScheduler()
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;
}

int ActObjScheduler::svc()
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;

    while ( true )
    {
        // Dequeue the next method object
        std::unique_ptr<ActiveObject_1_0::MethodRequest> request( this->mActivationQueue.dequeue() );

        // Invoke the method request.
        if ( request->call() == -1 )
        {
            break;
        }
    }
    return 0;
}

int ActObjScheduler::enqueue( ActiveObject_1_0::MethodRequest *request )
{
    cout << "ActObjScheduler::"
         << __FUNCTION__
         << endl;

    return mActivationQueue.enqueue( request );
}

} //namespace ExActiveObject
