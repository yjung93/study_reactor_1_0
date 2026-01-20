#include "AsynchOperation.hpp"
#include "framework/reactor/1_0/EventHandler.hpp"

namespace Proactor_1_0
{

int AsynchOperation::open( const Handler::Proxy_Ptr &handler_proxy,
                           int handle,
                           const void * /* completion_key */,
                           Proactor *proactor )
{
    this->proactor_ = proactor;
    this->handler_proxy_ = handler_proxy;
    this->handle_ = handle;

    // Grab the handle from the <handler> if <handle> is invalid
    if ( this->handle_ == INVALID_HANDLE )
    {
        Handler *handler = handler_proxy.get()->handler();
        if ( handler != 0 )
            this->handle_ = handler->handle();
    }
    if ( this->handle_ == INVALID_HANDLE )
        return -1;

    return 0;
}

int AsynchOperation::cancel()
{
    if ( !proactor_ )
        return -1;
    return proactor_->cancelAio( this->handle_ );
}

Proactor *AsynchOperation::proactor() const
{
    return this->proactor_;
}

AsynchOperation::~AsynchOperation()
{
}

AsynchOperation::AsynchOperation()
    : handle_( INVALID_HANDLE )
{
}

} // namespace Proactor_1_0