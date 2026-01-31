#ifndef PROACTOR_1_0_HANDLER_HPP_
#define PROACTOR_1_0_HANDLER_HPP_
#include <memory>

using namespace std;

namespace Proactor_1_0
{


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

    virtual void handleReadStream( const AsynchReadStreamResult &result ) {};
    virtual void handleWriteStream( const AsynchWriteStreamResult &result ) {};
    int handle();
    Proactor *proactor();
    void proactor( Proactor *p );

    class Proxy
    {
      public:
        Proxy( Handler *handler ) : mhandler( handler ) {}
        void reset() { this->mhandler = 0; }
        Handler *handler() { return this->mhandler; }

      private:
        Handler *mhandler;
    };

    typedef shared_ptr<Proxy> ProxyPtr;

    ProxyPtr &proxy();

  protected:
    Proactor *mProactor;
    ProxyPtr mProxy;
    int mHandle;
};

} // namespace Proactor_1_0

#endif // PROACTOR_1_0_HANDLER_HPP_