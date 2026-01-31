#ifndef PROACTOR_1_0_ASYNC_READ_STREAM_HPP_
#define PROACTOR_1_0_ASYNC_READ_STREAM_HPP_

#include <vector>

#include "AsynchResult.hpp"
#include "Proactor.hpp"
#include "Handler.hpp"

namespace Proactor_1_0
{

class AsynchReadStreamResult : public AsynchResult
{
  public:
    AsynchReadStreamResult( const Handler::ProxyPtr &handler_proxy,
                            int handle,
                            vector<uint8_t> &buffer,
                            size_t bytesToRead,
                            const void *act,
                            int priority,
                            int signal_number );

    virtual ~AsynchReadStreamResult();

    /// The number of bytes which were requested at the start of the
    /// asynchronous read.
    size_t bytesToRead() const;

    /// Message block which contains the read data.
    vector<uint8_t> &message() const;

    /// I/O handle used for reading.
    int handle() const;

    void complete( size_t bytes_transferred, int success, u_long error = 0 ) override;

  protected:
    vector<uint8_t> &mMessage;
};

class AsynchReadStream 
{
  public:
    AsynchReadStream();
    ~AsynchReadStream();

    int open( Handler &handler,
              int handle,
              const void *completionKey,
              Proactor *proactor = 0 );

    /// Check the documentation for ACE_Asynch_Operation::cancel.
    int cancel();

    // = Access methods.

    /// Return the underlying proactor.
    Proactor *proactor() const;

    int read( vector<uint8_t> &message,
              size_t bytesToRead,
              const void *act = 0,
              int priority = 0,
              int signal_number = SIGRTMIN );

  private:
    /// Proactor that this Asynch IO will be registered with.
    Proactor *mProactor;

    /// Handler that will receive the callback.
    Handler::ProxyPtr mhandlerProxy;

    /// I/O handle used for reading.
    int mHandle;
};
} // namespace Proactor_1_0

#endif // PROACTOR_1_0_ASYNC_READ_STREAM_HPP_