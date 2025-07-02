/*
 * Client.hpp
 *
 *  Created on: Jun 8, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_CLIENT_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_CLIENT_HPP_

#include "applications/example_acceptor_connector/OutputHandler.hpp"
#include "ConnectorImpl.hpp"

namespace ex_acceptor_connector
{

class Client
{
public:
    Client();
    virtual ~Client();

    void initialize();
    void finish();

    void sendMessage( string message );

private:

    ConnectorImpl mConnector;
    OutputHandler mOutputHandler;
};

} /* namespace v_1_1 */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_CLIENT_HPP_ */
