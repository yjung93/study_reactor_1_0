/*
 * OutputHandler.hpp
 *
 *  Created on: Jan 26, 2025
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_OutputHandler_HPP_
#define APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_OutputHandler_HPP_

#include "framework/v_1_1/ServiceHandler.hpp"
#include "framework/v_1_1/SockStream.hpp"

namespace ex_acceptor_connector
{

class OutputHandler: public v_1_1::ServiceHandler<v_1_1::SockStream>
{
public:
    OutputHandler();
    virtual ~OutputHandler();

    int close();
    void sendMessage( string message );

private:
    int handleInput( int fd = INVALID_HANDLE ) override;
};

} /* namespace ex_acceptor_connector */

#endif /* APPLICATIONS_EXAMPLE_ACCEPTOR_CONNECTOR_OutputHandler_HPP_ */
