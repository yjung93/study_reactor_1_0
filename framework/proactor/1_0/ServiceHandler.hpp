#ifndef PROACTOR_1_0_SERVICE_HANDLER_HPP_
#define PROACTOR_1_0_SERVICE_HANDLER_HPP_

#include "Handler.hpp"


using namespace std;

namespace Proactor_1_0
{

class ServiceHandler : public Handler
{
  public:
    ServiceHandler();
    virtual ~ServiceHandler();

    /**
   * {open} is called by Acceptor to initialize a new
   * instance of ServiceHandler that has been created after the
   * new connection is accepted. The handle for the new connection is
   * passed along with the initial data that may have shown up.
   */
    virtual void open( int new_handle );

    /// Called by Acceptor to pass the addresses of the new
    /// connections.
    virtual void addresses( const sockaddr_in &remote_address,
                            const sockaddr_in &local_address );

    /// Called by Acceptor to pass the act.
    virtual void act( const void * );
};

} // namespace Proactor_1_0

#endif // PROACTOR_1_0_SERVICE_HANDLER_HPP_