#ifndef PROACTOR_1_0_ASYNC_WRITE_STREAM_HPP_
#define PROACTOR_1_0_ASYNC_WRITE_STREAM_HPP_

#include "AsynchResult.hpp"
#include "AsynchOperation.hpp"

namespace Proactor_1_0
{

class AsynchWriteStreamResult : public AsynchResult
{
  public:
    AsynchWriteStreamResult( const Handler::Proxy_Ptr &handler_proxy,
                             int handle,
                             vector<uint8_t> &buffer,
                             size_t bytes_to_read,
                             const void *act,
                             int event,
                             int priority,
                             int signal_number );

    virtual ~AsynchWriteStreamResult();

    /// The number of bytes which were requested at the start of the
    /// asynchronous read.
    size_t bytes_to_write() const;

    /// Message block which contains the read data.
    vector<uint8_t> &message() const;

    /// I/O handle used for reading.
    int handle() const;

    void complete( size_t bytes_transferred, int success, const void *completion_key, u_long error = 0 ) override;

  protected:
    vector<uint8_t> &mMessage;
};

class AsynchWriteStream //: public AsynchOperation
{
  public:
    AsynchWriteStream();
    ~AsynchWriteStream();

    int open( Handler &handler,
              int handle,
              const void *completion_key,
              Proactor *proactor = 0 );

    /// Check the documentation for ACE_Asynch_Operation::cancel.
    int cancel();

    // = Access methods.

    /// Return the underlying proactor.
    Proactor *proactor() const;

    int write( vector<uint8_t> &message,
               size_t bytes_to_write,
               const void *act = 0,
               int priority = 0,
               int signal_number = SIGRTMIN );

  private:
    /// Proactor that this Asynch IO will be registered with.
    Proactor *proactor_;

    /// Handler that will receive the callback.
    Handler::Proxy_Ptr handler_proxy_;

    /// I/O handle used for reading.
    int handle_;
};
} // namespace Proactor_1_0

#endif // PROACTOR_1_0_ASYNC_WRITE_STREAM_HPP_