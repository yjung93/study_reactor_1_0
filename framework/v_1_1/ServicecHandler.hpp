/*
 * ServicecHandler.hpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_SERVICECHANDLER_HPP_
#define FRAMEWORK_V_1_1_SERVICECHANDLER_HPP_

#include "framework/v_1_1/EventHandler.hpp"
namespace v_1_1
{
template<typename PEER_STREAM>
class ServicecHandler: public EventHandler
{
public:
    ServicecHandler();
    virtual ~ServicecHandler();

    PEER_STREAM& peer() const;

protected:

    /// Maintain connection with client.
    PEER_STREAM mPeer;
};

} // namespace v_1_1

#endif /* FRAMEWORK_V_1_1_SERVICECHANDLER_HPP_ */
