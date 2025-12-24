#include <iostream>
#include <thread>

#include "ActivationQueue.hpp"

namespace ActiveObject_1_0
{

ActivationQueue::ActivationQueue()
{
}

ActivationQueue::~ActivationQueue()
{
}

MethodRequest *ActivationQueue::dequeue()
{
    MethodRequest *methodRequest = nullptr;

    unique_lock<mutex> lock( mQueueMutex );

    mQueueCondition.wait( lock,
                          [this]
                          { return !mMethodRequestQueue.empty(); } );

    if ( mMethodRequestQueue.empty() )
    {
        cout << "MethodRequest::"
             << __FUNCTION__
             << " mMethodRequestQueue is empty"
             << endl;
    }
    else
    {
        methodRequest = mMethodRequestQueue.front();

        thread::id this_id = this_thread::get_id();
        cout << "MethodRequest::"
             << __FUNCTION__
             << " threadId="
             << this_id
             << endl;

        mMethodRequestQueue.erase( mMethodRequestQueue.begin() );
    }

    return methodRequest;
}

int ActivationQueue::enqueue( MethodRequest *methodRequest )
{
    thread::id this_id = this_thread::get_id();

    cout << "ActivationQueue::"
         << __FUNCTION__
         << " threadId="
         << this_id
         << endl;

    lock_guard<mutex> guard( mQueueMutex );

    mMethodRequestQueue.push_back( methodRequest );
    mQueueCondition.notify_one();
    return 0;
}

} // namespace ActiveObject_1_0