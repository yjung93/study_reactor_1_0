#include <iostream>
#include <thread>

#include "ActivationQueue.hpp"

namespace ActiveObject_1_0
{

ActivationQueue::ActivationQueue()
    : mState( STATE_ACTIVE )
{
    cout << "ActivationQueue::"
         << __FUNCTION__ << ": "
         << endl;
}

ActivationQueue::~ActivationQueue()
{
    cout << "ActivationQueue::"
         << __FUNCTION__ << ": "
         << endl;
    exit();
}

MethodRequest *ActivationQueue::dequeue()
{
    MethodRequest *methodRequest = nullptr;

    unique_lock<mutex> lock( mQueueMutex );

    // mQueueCondition.wait( lock,
    //                       [this]
    //                       { return !mMethodRequestQueue.empty(); } );

    mQueueCondition.wait( lock );
    if ( mState == STATE_SHUTDOWN )
    {
        cout << "ActivationQueue::"
             << __FUNCTION__ << ": "
             << " exit"
             << endl;

        return methodRequest;
    }

    if ( mMethodRequestQueue.empty() )
    {
        cout << "ActivationQueue::"
             << __FUNCTION__ << ": "
             << " mMethodRequestQueue is empty"
             << endl;
    }
    else
    {
        methodRequest = mMethodRequestQueue.front();

        thread::id this_id = this_thread::get_id();
        cout << "ActivationQueue::"
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

void ActivationQueue::exit()
{
    cout << "ActivationQueue::"
         << __FUNCTION__ << ": "
         << endl;

    mState = STATE_SHUTDOWN;
    mQueueCondition.notify_one();
}

} // namespace ActiveObject_1_0