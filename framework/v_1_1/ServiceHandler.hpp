/*
 * ServiceHandler.hpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_ServiceHandler_HPP_
#define FRAMEWORK_V_1_1_ServiceHandler_HPP_

#include "framework/v_1_1/EventHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"

using namespace std;

namespace v_1_1
{
template<typename PEER_STREAM>
class ServiceHandler: public EventHandler
{
public:
    typedef typename PEER_STREAM::PEER_ADDR AddrType;
    typedef PEER_STREAM StreamType;

    ServiceHandler( Reactor *reactor );
    virtual ~ServiceHandler();
    virtual int open( void* );
    virtual int getHandle() const override;
    PEER_STREAM& peer() const;

protected:

    /// Maintain connection with client.
    PEER_STREAM mPeer;
};

} // namespace v_1_1

// for splitting the template class definition into .cpp
#include "framework/v_1_1/ServiceHandler.cpp"

#endif /* FRAMEWORK_V_1_1_ServiceHandler_HPP_ */
