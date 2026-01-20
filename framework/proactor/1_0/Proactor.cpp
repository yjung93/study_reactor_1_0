#include <string>
#include <iostream>

#include "Proactor.hpp"
#include "AsynchResult.hpp"

#include "framework/reactor/1_0/EventHandler.hpp"

namespace Proactor_1_0
{
Proactor *Proactor::mInstance = 0;

Proactor::Proactor()
    : mAiocbListMaxSize( _SC_AIO_MAX ),
      mAiocbListCurSize( 0 ),
      mAiocbList( mAiocbListMaxSize ),
      mResultList( mAiocbListMaxSize ),
      mNumDeferredAiocb( 0 ),
      mNumStartedAio( 0 ),
      mHandle( INVALID_HANDLE )
{
}

Proactor::~Proactor()
{
}

Proactor *Proactor::getInstance()
{
    if ( Proactor::mInstance == nullptr )
    {
        Proactor::mInstance = new Proactor();
    }

    return Proactor::mInstance;
}

ssize_t Proactor::allocateAioSlot( AsynchResult *result )
{
    size_t i = 0;

    // we reserve zero slot for ACE_AIOCB_Notify_Pipe_Manager
    // so make check for ACE_AIOCB_Notify_Pipe_Manager request

    if ( 0 ) //notify_pipe_read_handle_ == result->aio_fildes ) // Notify_Pipe ?
    {
        // should be free,
        if ( mAiocbList[i] != 0 ) // only 1 request
        { // is allowed
            errno = EAGAIN;

            cout << "Proactor::"
                 << __FUNCTION__
                 << ": "
                 << "internal Proactor error 0"
                 << endl;
        }
    }
    else //try to find free slot as usual, but starting from 1
    {
        for ( i = 1; i < this->mAiocbListMaxSize; i++ )
            if ( mAiocbList[i] == 0 )
                break;
    }

    if ( i >= this->mAiocbListMaxSize )
    {
        cout << "Proactor::"
             << __FUNCTION__
             << ": "
             << "internal Proactor error 1"
             << endl;
    }

    //setup OS notification methods for this aio
    result->aio_sigevent.sigev_notify = SIGEV_NONE;

    return static_cast<ssize_t>( i );
}

int Proactor::startAio( AsynchResult *result,
                        Proactor::Opcode op )
{
    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << endl;

    int returnValue = -1;
    if ( result == 0 ) // Just check the status of the list
        return returnValue;

    // Save operation code in the aiocb
    switch ( op )
    {
        case Proactor::OPCODE_READ:
            result->aio_lio_opcode = LIO_READ;
            break;

        case Proactor::OPCODE_WRITE:
            result->aio_lio_opcode = LIO_WRITE;
            break;

        default:
            cout << "Proactor::"
                 << __FUNCTION__
                 << ": "
                 << "Invalid op code="
                 << op
                 << endl;
    }

    ssize_t slot = allocateAioSlot( result );

    if ( slot < 0 )
        return -1;

    size_t index = static_cast<size_t>( slot );

    mResultList[index] = result; //Store result ptr anyway
    mAiocbListCurSize++;

    int rc = startAioI( result );

    cout << "Proactor::"
         << __FUNCTION__
         << ": startAioI "
         << " slot="
         << slot
         << " return value="
         << rc
         << endl;

    switch ( rc )
    {
        case 0: // started OK
            mAiocbList[index] = result;
            returnValue = 0;

        case 1: // OS AIO queue overflow
            mNumDeferredAiocb++;
            returnValue = 0;

        default: // Invalid request, there is no point
            break; // to start it later
    }

    if ( returnValue == -1 )
    {
        mResultList[index] = 0;
        mAiocbListCurSize--;
    }

    return returnValue;
}

int Proactor::startAioI( AsynchResult *result )
{
    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << endl;

    int returnValue = -1;
    string pPype;

    // Start IO
    // The following aio_ptr anathema is required to work around a bug in
    // the optimizer for GCC 4.1.2
    aiocb *aio_ptr( result );
    switch ( result->aio_lio_opcode )
    {
        case LIO_READ:
            pPype = "read ";
            returnValue = aio_read( aio_ptr );
            break;
        case LIO_WRITE:
            pPype = "write";
            returnValue = aio_write( aio_ptr );
            break;
        default:
            pPype = "?????";
            returnValue = -1;
            break;
    }

    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << " aio_fildes="
         << aio_ptr->aio_fildes
         << " aio_nbytes="
         << aio_ptr->aio_nbytes
         << " aio_offset="
         << aio_ptr->aio_offset
         << " aio_sigevent.sigev_signo="
         << aio_ptr->aio_sigevent.sigev_signo
         << " aio_sigevent.sigev_notify="
         << aio_ptr->aio_sigevent.sigev_notify
         << " pPype="
         << pPype
         << " return value="
         << returnValue
         << endl;

    if ( returnValue == 0 )
    {
        ++this->mNumStartedAio;
    }
    else // if (returnValue == -1)
    {
        if ( errno == EAGAIN || errno == ENOMEM ) //Ok, it will be deferred AIO
        {
            returnValue = 1;
        }
        else
        {
            cout << "Proactor::"
                 << __FUNCTION__
                 << ": "
                 << pPype
                 << " queueing failed"
                 << endl;
        }
    }

    return returnValue;
}

int Proactor::cancelAio( int handle )
{
    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << endl;

    return 0;
}

int Proactor::handleEvents()
{
    // cout << "Proactor::"
    //      << __FUNCTION__
    //      << ": "
    //      << endl;

    int resultSuspend = 0;
    int retval = 0;

    // Indefinite blocking.
    resultSuspend = aio_suspend( mAiocbList.data(),
                                 mAiocbList.size(),
                                 0 );

    // cout << "Proactor::"
    //      << __FUNCTION__
    //      << ": aio_suspend, resultSuspend="
    //      << resultSuspend
    //      << endl;

    // Check for errors
    if ( resultSuspend == -1 )
    {
        if ( errno != EAGAIN && // Timeout
             errno != EINTR ) // Interrupted call
        {
            cout << "Proactor::"
                 << __FUNCTION__
                 << ": "
                 << "aio_suspend Failed"
                 << endl;
        }

        // let continue work
        // we should check "post_completed" queue
    }
    else
    {
        size_t index = 0;
        size_t count = mAiocbListMaxSize; // max number to iterate
        int errorStatus = 0;
        size_t transferCount = 0;

        for ( ;; retval++ )
        {
            AsynchResult *AsynchResult = findCompletedAio( errorStatus,
                                                           transferCount,
                                                           index,
                                                           count );

            if ( AsynchResult == 0 )
                break;

            // Call the application code.
            this->applicationSpecificCode( AsynchResult,
                                           transferCount,
                                           0, // No completion key.
                                           errorStatus );
        }
    }

    // process post_completed results
    // retval += this->process_result_queue();

    return retval > 0 ? 1 : 0;
}

AsynchResult *Proactor::findCompletedAio( int &errorStatus,
                                          size_t &transferCount,
                                          size_t &index,
                                          size_t &count )
{
    // parameter index defines initial slot to scan
    // parameter count tells us how many slots should we scan

    // ACE_MT( ACE_GUARD_RETURN( ACE_Thread_Mutex, ace_mon, this->mutex_, 0 ) );

    // cout << "Proactor::"
    //      << __FUNCTION__
    //      << ": "
    //      << " transferCount="
    //      << transferCount
    //      << " index="
    //      << index
    //      << " count="
    //      << count
    //      << " mAiocbListMaxSize="
    //      << mAiocbListMaxSize
    //      << endl;

    AsynchResult *AsynchResult = 0;

    if ( mNumStartedAio == 0 ) // save time
        return 0;

    for ( ; count > 0; index++, count-- )
    {
        if ( index >= mAiocbListMaxSize ) // like a wheel
        {
            index = 0;
        }

        if ( mAiocbList[index] == nullptr ) // Dont process null blocks.
        {
            continue;
        }

        if ( 0 != this->getResultStatus( mResultList[index],
                                         errorStatus,
                                         transferCount ) ) // completed
        {
            break;
        }

    } // end for

    if ( count == 0 ) // all processed , nothing found
    {
        cout << "Proactor::"
             << __FUNCTION__
             << ": "
             << "all processed , nothing found."
             << " transferCount="
             << transferCount
             << " index="
             << index
             << " count="
             << count
             << " mAiocbListMaxSize="
             << mAiocbListMaxSize
             << endl;
        return 0;
    }

    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << "found completed ."
         << " transferCount="
         << transferCount
         << " index="
         << index
         << " count="
         << count
         << " mAiocbListMaxSize="
         << mAiocbListMaxSize
         << endl;

    AsynchResult = mResultList[index];

    mAiocbList[index] = 0;
    mResultList[index] = 0;
    mAiocbListCurSize--;

    mNumStartedAio--; // decrement count active aios
    index++; // for next iteration
    count--; // for next iteration

    // this->start_deferred_aio();
    //make attempt to start deferred AIO
    //It is safe as we are protected by mutex_

    return AsynchResult;
}

int Proactor::getResultStatus( AsynchResult *asynchResult,
                               int &errorStatus,
                               size_t &transferCount )
{
    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << " aio_fildes="
         << asynchResult->aio_fildes
         << " aio_nbytes="
         << asynchResult->aio_nbytes
         << " aio_offset="
         << asynchResult->aio_offset
         << " aio_sigevent.sigev_signo="
         << asynchResult->aio_sigevent.sigev_signo
         << " aio_sigevent.sigev_notify="
         << asynchResult->aio_sigevent.sigev_notify
         << endl;

    transferCount = 0;

    // Get the error status of the aio_ operation.
    // The following aio_ptr anathema is required to work around a bug in an over-aggressive
    // optimizer in GCC 4.1.2.
    aiocb *aio_ptr( asynchResult );
    errorStatus = aio_error( aio_ptr );
    if ( errorStatus == EINPROGRESS )
    {
        cout << "Proactor::"
             << __FUNCTION__
             << ": "
             << "errorStatus="
             << errorStatus
             << endl;
        return 0; // not completed
    }

    ssize_t op_return = aio_return( aio_ptr );
    if ( op_return > 0 )
    {
        transferCount = static_cast<size_t>( op_return );
    }
    // else transferCount is already 0, errorStatus reports the error.
    return 1; // completed
}

int Proactor::startDeferredAio()
{
    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << endl;

    // This protected method is called from
    // find_completed_aio after any AIO completion
    // We should call this method always with locked
    // ACE_POSIX_AIOCB_Proactor::mutex_
    //
    // It tries to start the first deferred AIO
    // if such exists

    if ( mNumDeferredAiocb == 0 )
        return 0; //  nothing to do

    size_t i = 0;

    for ( i = 0; i < this->mAiocbListMaxSize; i++ )
    {
        if ( mResultList[i] != 0 // check for
             && mAiocbList[i] == 0 ) // deferred AIO
        {
            break;
        }
    }

    if ( i >= this->mAiocbListMaxSize )
    {
        cout << "Proactor::"
             << __FUNCTION__
             << ": "
             << "internal Proactor error 3\n"
             << endl;
    }

    AsynchResult *result = mResultList[i];

    int rc = startAioI( result );

    switch ( rc )
    {
        case 0: //started OK , decrement count of deferred AIOs
            mAiocbList[i] = result;
            mNumDeferredAiocb--;
            return 0;

        case 1:
            return 0; //try again later

        default: // Invalid Parameters , should never be
            break;
    }

    //AL notify  user

    mResultList[i] = 0;
    --mAiocbListCurSize;

    --mNumDeferredAiocb;

    result->set_error( errno );
    result->set_bytes_transferred( 0 );
    this->putqResult( result ); // we are with locked mutex_ here !

    return -1;
}

int Proactor::putqResult( AsynchResult *result )
{
    // this protected method should be called with locked mutex_
    // we can't use GUARD as Proactor uses non-recursive mutex

    if ( !result )
        return -1;

    int sigNum = result->signal_number();
    this->mResultQueue.push_back( result );

    (void) sigNum; // avoid unused variable
    // Jake, TBD, this->notify_completion(sigNum   );

    return 0;
}

void Proactor::applicationSpecificCode( AsynchResult *asynchResult,
                                        size_t bytes_transferred,
                                        const void * /* completion_key*/,
                                        u_long error )
{
    // ACE_SEH_TRY
    {
        // Call completion hook
        asynchResult->complete( bytes_transferred,
                                error ? 0 : 1,
                                0, // No completion key.
                                error );
    }
    // ACE_SEH_FINALLY
    {
        // This is crucial to prevent memory leaks
        delete asynchResult;
    }
}

int Proactor::proactorRunEventLoop()
{
    cout << "Proactor::"
         << __FUNCTION__
         << ": "
         << endl;

    int result = 0;

    {
        // ACE_MT( ACE_GUARD_RETURN( ACE_Thread_Mutex, ace_mon, mutex_, -1 ) );

        // Early check. It is ok to do this without lock, since we care just
        // whether it is zero or non-zero.
        if ( this->mEndEventLoop != 0 )
            return 0;

        // First time you are in. Increment the thread count.
        this->mEventLoopThreadCount++;
    }

    // Run the event loop.
    for ( ;; )
    {
        // Check the end loop flag. It is ok to do this without lock,
        // since we care just whether it is zero or non-zero.
        if ( this->mEndEventLoop != 0 )
            break;

        // <end_event_loop> is not set. Ready to do <handle_events>.
        result = this->handleEvents();

        if ( result == -1 )
            break;
    }

    // Leaving the event loop. Decrement the thread count.

    {
        // Obtain the lock in the MT environments.
        // ACE_MT( ACE_GUARD_RETURN( ACE_Thread_Mutex, ace_mon, mutex_, -1 ) );

        // Decrement the thread count.
        this->mEventLoopThreadCount--;

        if ( this->mEventLoopThreadCount > 0 && this->mEndEventLoop != 0 )
            this->postWakeupCompletions( 1 );
    }

    return result;
}

int Proactor::postWakeupCompletions( int how_many )
{
    // Jake TBD
    //   ACE_POSIX_Wakeup_Completion *wakeupCompletion = 0;

    //   for (int ci = 0; ci < how_many; ci++)
    //     {
    //       ACE_NEW_RETURN
    //         (wakeupCompletion,
    //          ACE_POSIX_Wakeup_Completion (this->wakeup_handler_.proxy ()),
    //          -1);
    //       if (this->postCompletion (wakeupCompletion) == -1)
    //         return -1;
    //     }

    return 0;
}

int Proactor::postCompletion( AsynchResult *result )
{
    //   ACE_MT (ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, ace_mon, this->mutex_, -1));

    int ret_val = this->putqResult( result );

    return ret_val;
}

int Proactor::get_handle() const
{
    return mHandle;
}

} // namespace Proactor_1_0