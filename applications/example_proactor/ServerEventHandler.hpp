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
#include "framework/proactor/1_0/AsynchWriteStream.hpp"

namespace example_proactor
{

class Acceptor;

class ServerEventHandler : public Proactor_1_0::ServiceHandler
{
  public:
    const int messageSize = 8;
    ServerEventHandler( Acceptor &owner );
    ~ServerEventHandler();
    void open( int new_handle ) override;
    void handle_read_stream( const Proactor_1_0::AsynchReadStreamResult &result ) override;
    void handle_write_stream( const Proactor_1_0::AsynchWriteStreamResult &result ) override;

  private:

    Acceptor *mOwner;
    Proactor_1_0::AsynchReadStream mReader; // Async read
    Proactor_1_0::AsynchWriteStream mWriter; // Async read
    vector<uint8_t> mMessageRead;
    vector<uint8_t> mMessageWrite;
};

} /* namespace example_proactor */

#endif /* APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_ */
