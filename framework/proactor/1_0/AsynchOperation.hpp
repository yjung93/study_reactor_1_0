#ifndef PROACTOR_1_0_ASYNC_OPERATION_HPP_
#define PROACTOR_1_0_ASYNC_OPERATION_HPP_

#include "Proactor.hpp"
#include "Handler.hpp"

namespace Proactor_1_0
{
class AsynchOperation
{

  int open (const Handler::Proxy_Ptr &handler_proxy,
            int handle,
            const void *completion_key,
            Proactor *proactor = 0);

  int cancel ();

  /// Return the underlying proactor.
  Proactor* proactor () const;

protected:
  /// Constructor.
  AsynchOperation ();

  /// Destructor.
  virtual ~AsynchOperation ();


  /// Proactor that this Asynch IO will be registered with.
  Proactor *proactor_;

  /// Handler that will receive the callback.
  Handler::Proxy_Ptr handler_proxy_;

  /// I/O handle used for reading.
  int handle_;
};
} // namespace Proactor_1_0

#endif // PROACTOR_1_0_ASYNC_OPERATION_HPP_