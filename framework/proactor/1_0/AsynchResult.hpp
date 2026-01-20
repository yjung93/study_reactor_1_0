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

    /**
   * This is the ACT associated with the handle on which the
   * Asynch_Operation takes place.
   *
   * @note This is not implemented for POSIX4 platforms.
   */
    const void *completion_key() const;

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
    u_long offset_high() const;

    /// Priority of the operation.
    int priority() const;

    /**
   * POSIX4 realtime signal number to be used for the
   * operation. <signal_number> ranges from SIGRTMIN to SIGRTMAX. By
   * default, SIGRTMIN is used to issue <aio_> calls.
   */
    int signal_number() const;

    /// Post @c this to the Proactor.
    int post_completion( Proactor *proactor );

    /// Destructor.
    virtual ~AsynchResult();

    /// Simulate error value to use in the post_completion ()
    void set_error( u_long errcode );

    /// Simulate value to use in the post_completion ()
    void set_bytes_transferred( size_t nbytes );

    virtual void complete( size_t bytes_transferred,
                           int success,
                           const void *completion_key,
                           u_long error = 0 ) = 0;

  protected:
    /// Constructor. <Event> is not used on POSIX.
    AsynchResult( const Handler::Proxy_Ptr &handler_proxy,
                  const void *act,
                  int event,
                  u_long offset,
                  u_long offset_high,
                  int priority,
                  int signal_number );


    /// Handler that will be called back.
    Handler::Proxy_Ptr handler_proxy_;

    /**
   * ACT for this operation.
   * We could use <aiocb::aio_sigevent.sigev_value.sival_ptr> for
   * this. But it doesnot provide the constness, so this may be
   * better.
   */
    const void *act_;

    /// Bytes transferred by this operation.
    size_t bytes_transferred_;

    /// Success indicator.
    int success_;

    /// ACT associated with handle.
    const void *completion_key_;

    /// Error if operation failed.
    u_long error_;
};

} // namespace Proactor_1_0

#endif // PROACTOR_1_0_ASYNC_RESULT_HPP_