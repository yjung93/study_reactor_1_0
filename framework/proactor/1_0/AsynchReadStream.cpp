#include "AsynchReadStream.hpp"

namespace Proactor_1_0
{

AsynchReadStreamResult::AsynchReadStreamResult( const Handler::Proxy_Ptr &handler_proxy,
                                                int handle,
                                                vector<uint8_t> &message,
                                                size_t bytes_to_read,
                                                const void *act,
                                                int event,
                                                int priority,
                                                int signal_number )
    : AsynchResult( handler_proxy,
                    act,
                    event,
                    0,
                    0,
                    priority,
                    signal_number ),
      mMessage( message )
{
    this->aio_fildes = handle;
    this->aio_nbytes = message.size();

    if ( message.size() > 0 )
    {
        // Use the string buffer. Caller must ensure message is resized to hold data.
        this->aio_buf = message.data();
    }
    else
    {
        this->aio_buf = nullptr;
    }

    cout << "AsynchResult::"
         << __FUNCTION__
         << ": "
         << " aio_fildes="
         << aio_fildes
         << " aio_nbytes="
         << aio_nbytes
         << " aio_offset="
         << aio_offset
         << " aio_sigevent.sigev_signo="
         << aio_sigevent.sigev_signo
         << " aio_sigevent.sigev_notify="
         << aio_sigevent.sigev_notify
         << endl;
}

AsynchReadStreamResult::~AsynchReadStreamResult()
{
}

size_t AsynchReadStreamResult::bytes_to_read() const
{
    return this->aio_nbytes;
}

/// Message block which contains the read data.
vector<uint8_t> &AsynchReadStreamResult::message() const
{
    return this->mMessage;
}

/// I/O handle used for reading.
int AsynchReadStreamResult::handle() const
{
    return this->aio_fildes;
}

void AsynchReadStreamResult::complete( size_t bytes_transferred, int success, const void *completion_key, u_long error )
{
    this->bytes_transferred_ = bytes_transferred;
    this->success_ = success;
    this->completion_key_ = completion_key;
    this->error_ = error;

    // <errno> is available in the aiocb.
    (void) error;

    // Appropriately move the pointers in the message block.
    // this->message_block_.wr_ptr( bytes_transferred );

    // Create the interface result class.
    // ACE_Asynch_Read_Stream::Result result( this );

    // Call the application handler.
    Handler *handler = this->handler_proxy_.get()->handler();
    if ( handler != 0 )
    {
        handler->handle_read_stream( *this );
    }
}

AsynchReadStream::AsynchReadStream()
{
}
AsynchReadStream::~AsynchReadStream()
{
}

int AsynchReadStream::read( vector<uint8_t> &message,
                            size_t bytes_to_read,
                            const void *act,
                            int priority,
                            int signal_number )
{
    cout << "AsynchReadStream::"
         << __FUNCTION__
         << ": "
         << endl;
    // size_t space = message.space();
    // if ( bytes_to_read > space )
    //     bytes_to_read = space;

    if ( bytes_to_read == 0 )
    {
        errno = ENOSPC;
        return -1;
    }

    // Create the Asynch_Result.

    Proactor *proactor = this->proactor();
    AsynchReadStreamResult *result = new AsynchReadStreamResult( this->handler_proxy_,
                                                                 this->handle_,
                                                                 message,
                                                                 bytes_to_read,
                                                                 act,
                                                                 proactor->get_handle(),
                                                                 priority,
                                                                 signal_number );

    int return_val = proactor->startAio( result, Proactor::OPCODE_READ );
    cout << "AsynchReadStream::"
         << __FUNCTION__
         << ": "
         << "return_val="
         << return_val
         << endl;
    if ( return_val == -1 )
    {
        delete result;
    }

    return return_val;
}

int AsynchReadStream::open( Handler &handler,
                            int handle,
                            const void *completion_key,
                            Proactor *proactor )
{
    cout << "AsynchReadStream::"
         << __FUNCTION__
         << ": "
         << endl;

    proactor_ = proactor;
    handler_proxy_ = handler.proxy();
    handle_ = handle;
    if ( proactor_ == nullptr )
    {
        proactor_ = Proactor::getInstance();
    }
    return 0;
}

Proactor *AsynchReadStream::proactor() const
{
    return proactor_;
}
} // namespace Proactor_1_0