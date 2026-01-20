/*
 * ServerEventHandler.h
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_
#define APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_

#include "framework/reactor/1_0/EventHandler.hpp"
#include "framework/reactor/1_0/Reactor.hpp"

#include "framework/proactor/1_0/AsynchReadStream.hpp"
#include "framework/proactor/1_0/ServiceHandler.hpp"
#include "framework/proactor/1_0/AsynchReadStream.hpp"

namespace example_proactor
{

class Acceptor;

class ServerEventHandler : public Proactor_1_0::ServiceHandler
{
  public:
    const int messageSize = 8;
    ServerEventHandler( Acceptor &owner );
    virtual ~ServerEventHandler();
    virtual void open( int new_handle ) override;
    virtual void handle_read_stream( const Proactor_1_0::AsynchReadStreamResult &result ) override;

  private:
    // int handleInput( int fd = INVALID_HANDLE ) override;

    Acceptor *mOwner;
    Proactor_1_0::AsynchReadStream mReader; // Async read factory
    vector<uint8_t> mMessage;
};

} /* namespace example_proactor */

#endif /* APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_ */
