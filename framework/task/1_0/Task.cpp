/*
 * Task.hpp
 *
 *  Created on: Nov 04, 2025
 *      Author: yjung93
 */

#include <iostream>
#include <system_error>
#include "Task.hpp"

using namespace std;

namespace Task_1_0
{

Task::Task()
    : mStopRequested( false )
{
    cout << "Task::"
         << __FUNCTION__
         << endl;
}

Task::~Task()
{
    cout << "Task::"
         << __FUNCTION__
         << endl;
    {
        lock_guard<mutex> guard( mQueueMutex );
        mStopRequested = true;
    }

    mQueueCondition.notify_all();

    if ( mWorkerThread.joinable() )
    {
        mWorkerThread.join();
    }
}
int Task::open( void *args )
{
    cout << "Task::"
         << __FUNCTION__
         << ": "
         << "Default open implementation. Override in derived class."
         << endl;
    return 0;
}

int Task::activate()
{
    if ( mWorkerThread.joinable() )
    {
        return -1; // Thread already running
    }

    try
    {
        mWorkerThread = thread( &Task::svcRun, this );
    }
    catch ( const system_error &ex )
    {
        cerr << "Task::activate failed: " << ex.what() << endl;
        return -1;
    }

    return 0;
}

int Task::putQ( const string &message )
{
    thread::id this_id = this_thread::get_id();

    cout << "Task::"
         << __FUNCTION__
         << " threadId="
         << this_id
         << ": message="
         << message
         << endl;

    lock_guard<mutex> guard( mQueueMutex );

    if ( mStopRequested )
    {
        return -1;
    }

    mMessageQueue.push_back( message );
    mQueueCondition.notify_one();

    return 0;
}

int Task::getQ( string &message )
{
    int returnCode = 0;

    unique_lock<mutex> lock( mQueueMutex );

    mQueueCondition.wait( lock,
                          [this]
                          { return mStopRequested || !mMessageQueue.empty(); } );

    if ( mMessageQueue.empty() )
    {
        returnCode = -1; // Queue is empty
    }
    else
    {
        message = mMessageQueue.front();

        thread::id this_id = this_thread::get_id();
        cout << "Task::"
             << __FUNCTION__
             << " threadId="
             << this_id
             << ": message="
             << message
             << endl;

        mMessageQueue.erase( mMessageQueue.begin() );
    }
    return returnCode;
}

int Task::svcRun()
{
    bool returnCode = false;
    returnCode = svc();

    return returnCode;
}

int Task::svc()
{
    cout << "Task::"
         << __FUNCTION__
         << ": "
         << "Default svc implementation. Override in derived class."
         << endl;
    return 0;
}
} // namespace Task_1_0
