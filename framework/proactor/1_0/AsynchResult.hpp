#ifndef PROACTOR_1_0_ASYNC_RESULT_HPP_
#define PROACTOR_1_0_ASYNC_RESULT_HPP_

#include <aio.h>
#include <iostream>
#include "Handler.hpp"

using namespace std;

namespace Proactor_1_0
{

class Proactor;

class AsynchResult : public aiocb
{
  public:
    /// Number of bytes transferred by the operation.
    size_t bytes_transferred() const;

    /// ACT associated with the operation.
    const void *act() const;

    /// Did the operation succeed?
    int success() const;

    /// Error value if the operation fails.
    u_long error() const;

    /// This returns ACE_INVALID_HANDLE on POSIX4 platforms.
    int event() const;

    /**
   * This really make sense only when doing file I/O.
   *
   * @@ On POSIX4-Unix, offset_high should be supported using
   *     aiocb64.
   *
   */
    u_long offset() const;
    u_long offsetHigh() const;

    /// Priority of the operation.
    int priority() const;

    /**
   * POSIX4 realtime signal number to be used for the
   * operation. <signal_number> ranges from SIGRTMIN to SIGRTMAX. By
   * default, SIGRTMIN is used to issue <aio_> calls.
   */
    int signalNumber() const;

    /// Post @c this to the Proactor.
    int postCompletion( Proactor *proactor );

    /// Destructor.
    virtual ~AsynchResult();

    /// Simulate error value to use in the post_completion ()
    void setError( u_long errcode );

    /// Simulate value to use in the post_completion ()
    void setBytesTransferred( size_t nbytes );

    virtual void complete( size_t bytes_transferred,
                           int success,
                           u_long error = 0 ) = 0;

  protected:
    AsynchResult( const Handler::ProxyPtr &handler_proxy,
                  const void *act,
                  u_long offset,
                  u_long offset_high,
                  int priority,
                  int signal_number );


    /// Handler that will be called back.
    Handler::ProxyPtr mhandlerProxy;

    /**
   * ACT for this operation.
   * We could use <aiocb::aio_sigevent.sigev_value.sival_ptr> for
   * this. But it doesnot provide the constness, so this may be
   * better.
   */
    const void *mAct;

    /// Bytes transferred by this operation.
    size_t mBytesTransferred;

    /// Success indicator.
    int mSuccess;

    /// Error if operation failed.
    u_long mError;
};

} // namespace Proactor_1_0

#endif // PROACTOR_1_0_ASYNC_RESULT_HPP_