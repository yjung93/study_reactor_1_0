/*
 * ServiceHandler.cpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_ServiceHandler_CPP_
#define FRAMEWORK_V_1_1_ServiceHandler_CPP_

#include <iostream>
#include "ServiceHandler.hpp"
namespace v_1_1
{

template<typename PEER_STREAM>
ServiceHandler<PEER_STREAM>::ServiceHandler( Reactor *reactor ) :
                EventHandler( reactor )
{
    cout << "ServiceHandler<PEER_STREAM>::" << __FUNCTION__ << ": " << endl;
}
template<typename PEER_STREAM>
ServiceHandler<PEER_STREAM>::~ServiceHandler()
{
    cout << "ServiceHandler<PEER_STREAM>::" << __FUNCTION__ << ": " << endl;
}

template<typename PEER_STREAM>
PEER_STREAM& ServiceHandler<PEER_STREAM>::peer() const
{
    cout << "ServiceHandler<PEER_STREAM>::" << __FUNCTION__ << ": " << endl;

    return (PEER_STREAM&) this->mPeer;
}
template<typename PEER_STREAM>
int ServiceHandler<PEER_STREAM>::getHandle() const
{
    return mPeer.getHandle();
}

template<typename PEER_STREAM>
int ServiceHandler<PEER_STREAM>::open( void* )
{
    cout << "ServiceHandler<PEER_STREAM>::" << __FUNCTION__ << ": " << endl;
    int result = 0;
    if ( getReactor() != nullptr )
    {
        int rc = getReactor()->registerHandler( this, EventHandler::READ_MASK );
        if ( rc == -1 )
        {
            result = -1;
        }
    }
    return result;
}

} // namespace v_1_1


#endif /* FRAMEWORK_V_1_1_ServiceHandler_HPP_ */
