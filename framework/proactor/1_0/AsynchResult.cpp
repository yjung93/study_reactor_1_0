#include <cstring> 

#include "AsynchResult.hpp"
#include "Proactor.hpp"
#include "Handler.hpp"

#include "framework/reactor/1_0/EventHandler.hpp"

namespace Proactor_1_0
{

size_t AsynchResult::bytes_transferred() const
{
    return this->bytes_transferred_;
}

void AsynchResult::set_bytes_transferred( size_t nbytes )
{
    this->bytes_transferred_ = nbytes;
}

const void *AsynchResult::act() const
{
    return this->act_;
}

int AsynchResult::success() const
{
    return this->success_;
}

const void *AsynchResult::completion_key() const
{
    return this->completion_key_;
}

u_long AsynchResult::error() const
{
    return this->error_;
}

void AsynchResult::set_error( u_long errcode )
{
    this->error_ = errcode;
}

int AsynchResult::event() const
{
    return INVALID_HANDLE;
}

u_long AsynchResult::offset() const
{
    return this->aio_offset;
}

u_long AsynchResult::offset_high() const
{
    // errno = ENOTSUP;
    return 0;
}

int AsynchResult::priority() const
{
    return this->aio_reqprio;
}

int AsynchResult::signal_number() const
{
    return this->aio_sigevent.sigev_signo;
}

int AsynchResult::post_completion( Proactor *proactor )
{
    // Get to the platform specific implementation.

    if ( proactor == 0 )
    {
        cout << "AsynchResult::"
             << __FUNCTION__
             << ": "
             << "proactor null pointer"
             << endl;
        return -1;
    }

    // Post myself.
    return proactor->postCompletion( this );
}

AsynchResult::~AsynchResult()
{
}

AsynchResult::AsynchResult( const Handler::Proxy_Ptr &handler_proxy,
                            const void *act,
                            int /* event */, // Event is not used on POSIX.
                            u_long offset,
                            u_long offset_high,
                            int priority,
                            int signal_number )

    : handler_proxy_( handler_proxy ),
      act_( act ),
      bytes_transferred_( 0 ),
      success_( 0 ),
      completion_key_( 0 ),
      error_( 0 )
{
    ::memset(static_cast<aiocb*>(this), 0, sizeof(aiocb));

    aio_offset = offset;
    aio_reqprio = priority;
    aio_sigevent.sigev_signo = signal_number;
    aio_sigevent.sigev_notify = SIGEV_NONE; 
    //
    // @@ Support offset_high with aiocb64.
    //
    (void) offset_high;

    // Other fields in the <aiocb> will be initialized by the
    // subclasses.
}

} // namespace Proactor_1_0