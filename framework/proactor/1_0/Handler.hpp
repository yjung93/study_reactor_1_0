#ifndef PROACTOR_1_0_HANDLER_HPP_
#define PROACTOR_1_0_HANDLER_HPP_
#include <memory>
// #include "AsynchReadStream.hpp"
using namespace std;

namespace Proactor_1_0
{

// class AsynchReadStream;
class AsynchWriteStream;
class Proactor;
class AsynchReadStream;
class AsynchReadStreamResult;
class AsynchWriteStream;
class AsynchWriteStreamResult;

class Handler
{
  public:
    Handler();
    Handler( Proactor *p );
    virtual ~Handler();

    virtual void handle_read_stream( const AsynchReadStreamResult &result ) {};
    virtual void handle_write_stream( const AsynchWriteStreamResult &result ) {};
    int handle();
    Proactor *proactor();
    void proactor( Proactor *p );

    class Proxy
    {
      public:
        Proxy( Handler *handler ) : handler_( handler ) {}
        void reset() { this->handler_ = 0; }
        Handler *handler() { return this->handler_; }

      private:
        Handler *handler_;
    };

    typedef shared_ptr<Proxy> Proxy_Ptr;

    Proxy_Ptr &proxy();

  protected:
    Proactor *proactor_;
    Proxy_Ptr proxy_;
    int handle_;
};

} // namespace Proactor_1_0

#endif // PROACTOR_1_0_HANDLER_HPP_