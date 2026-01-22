#ifndef PROACTOR_1_0_PROACTOR_HPP_
#define PROACTOR_1_0_PROACTOR_HPP_

#include <vector>
#include <deque>
#include <signal.h>
#include <mutex>

#include "AsynchResult.hpp"

using namespace std;

namespace Proactor_1_0
{
class NotifyPipeManager;

class Proactor
{
    friend class NotifyPipeManager;

  public:
    enum Opcode
    {
        OPCODE_READ = 1,
        OPCODE_WRITE = 2
    };

    Proactor();
    ~Proactor();

    int startAio( AsynchResult *result, Proactor::Opcode op );
    int startAioI( AsynchResult *result );
    int cancelAio( int handle );

    static Proactor *getInstance();
    int proactorRunEventLoop();

    int postWakeupCompletions( int how_many );
    int postCompletion( AsynchResult *result );
    int get_handle() const;
    int notifyCompletion();

  protected:
    int handleEvents();
    AsynchResult *findCompletedAio( int &error_status,
                                    size_t &transfer_count,
                                    size_t &index,
                                    size_t &count );

    int getResultStatus( AsynchResult *asynchResult,
                         int &errorStatus,
                         size_t &transferCount );

    int startDeferredAio();

    int putqResult( AsynchResult *result );

    void applicationSpecificCode( AsynchResult *asynch_result,
                                  size_t bytes_transferred,
                                  const void *completion_key,
                                  u_long error );

    ssize_t allocateAioSlot( AsynchResult *result );

    void createNotifyManager();
    int createResultAiocbList();
    int deleteResultAiocbList();
    void setNotifyHandle( int h );

    static Proactor *mInstance;

    //to keep track of all the aio's
    // issued currently.
    aiocb **mAiocbList;
    AsynchResult **mResultList;

    /// To maintain the maximum size of the array (list).
    size_t mAiocbListMaxSize;

    /// To maintain the current size of the array (list).
    size_t mAiocbListCurSize;

    /// Number of ACE_POSIX_Asynch_Result's waiting for start
    /// i.e. deferred AIOs
    size_t mNumDeferredAiocb;

    /// Number active,i.e. running requests
    size_t mNumStartedAio;

    /// Queue which keeps "post_completed" AsynchResult's
    std::deque<AsynchResult *> mResultQueue;

    /// Terminate the proactor event loop.
    sig_atomic_t mEndEventLoop;

    /// Number of threads in the event loop.
    sig_atomic_t mEventLoopThreadCount;

    int mHandle;

    NotifyPipeManager *mAiocbNotifyPipeManager;
    int mNotifyPipeReadHandle;
    recursive_mutex mRecursiveMutex;
};

} // namespace Proactor_1_0

#endif // PROACTOR_1_0_PROACTOR_HPP_