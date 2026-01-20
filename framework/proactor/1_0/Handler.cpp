#include "Handler.hpp"
#include "Proactor.hpp"
#include "framework/reactor/1_0/EventHandler.hpp"

namespace Proactor_1_0
{

Handler::Handler()
    : proactor_( 0 ), handle_( INVALID_HANDLE )
{
    Handler::Proxy *p = new Handler::Proxy( this );
    this->proxy_.reset( p );
}

Handler::Handler( Proactor *d )
    : proactor_( d ), handle_( INVALID_HANDLE )
{
    Handler::Proxy *p = new Handler::Proxy( this );
    this->proxy_.reset( p );
}

Handler::~Handler()
{
    Handler::Proxy *p = this->proxy_.get();
    if ( p )
        p->reset();
}

int Handler::handle()
{
    return handle_;
}

Proactor *Handler::proactor()
{
    return this->proactor_;
}

void Handler::proactor( Proactor *p )
{
    this->proactor_ = p;
}

Handler::Proxy_Ptr &Handler::proxy()
{
    return proxy_;
}
} // namespace Proactor_1_0