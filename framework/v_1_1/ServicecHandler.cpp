/*
 * ServicecHandler.cpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */
#include <iostream>
#include "ServicecHandler.hpp"

template<typename PEER_STREAM>
ServicecHandler<PEER_STREAM>::ServicecHandler()
{
    // TODO Auto-generated constructor stub

}
template<typename PEER_STREAM>
ServicecHandler<PEER_STREAM>::~ServicecHandler()
{
    // TODO Auto-generated destructor stub
}

template<typename PEER_STREAM>
PEER_STREAM& ServicecHandler<PEER_STREAM>::peer() const
{
    std::cout << "ServicecHandler<PEER_STREAM>::peer"
              << std::endl;

    return (PEER_STREAM&) this->mPeer;
}
