/*
 * ServiceHandler.hpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#ifndef FRAMEWORK_ACCEPTOR_CONNECTOR_1_0_ServiceHandler_HPP_
#define FRAMEWORK_ACCEPTOR_CONNECTOR_1_0_ServiceHandler_HPP_

#include "framework/reactor/1_0/EventHandler.hpp"
#include "framework/reactor/1_0/Reactor.hpp"

using namespace std;

namespace AcceptorConnector_1_0
{
template<typename PEER_STREAM>
class ServiceHandler: public Reactor_1_0::EventHandler
{
public:
    typedef typename PEER_STREAM::PEER_ADDR AddrType;
    typedef PEER_STREAM StreamType;

    ServiceHandler( Reactor_1_0::Reactor *reactor );
    virtual ~ServiceHandler();
    virtual int open( void* );
    virtual int getHandle() const override;
    PEER_STREAM& peer() const;

protected:

    /// Maintain connection with client.
    PEER_STREAM mPeer;
};

} // namespace AcceptorConnector_1_0

// for splitting the template class definition into .cpp
#include "framework/acceptor_connector/1_0/ServiceHandler.cpp"

#endif /* FRAMEWORK_ACCEPTOR_CONNECTOR_1_0_ServiceHandler_HPP_ */
