/*
 * Connector.hpp
 *
 *  Created on: Jan 14, 2025
 *      Author: yjung93
 */

#ifndef FRAMEWORK_V_1_1_CONNECTOR_HPP_
#define FRAMEWORK_V_1_1_CONNECTOR_HPP_




#include "framework/v_1_1/Config.hpp"
#include "framework/v_1_1/EventHandler.hpp"
#include "framework/v_1_1/Reactor.hpp"

using namespace std;

namespace v_1_1
{
template<typename SVC_HANDLER, typename PEER_CONNECTOR>
class Connector: public EventHandler
{
public:
    typedef typename SVC_HANDLER::AddrType AddrType;
    typedef PEER_CONNECTOR ConnectorType;
    typedef SVC_HANDLER HandlerType;
    typedef typename SVC_HANDLER::StreamType streamType;
    typedef typename PEER_CONNECTOR::PEER_ADDR PeerAddrType;
    typedef typename PEER_CONNECTOR::PEER_ADDR PEER_ADDR_TYPEDEF;

    Connector( Reactor *reactor = 0, int flags = 0 );
    virtual ~Connector();

    virtual int open( Reactor *reactor = Reactor::getInstance(), int flags = 0 );

    /// Set Reactor.
    virtual void setReactor( Reactor *reactor );

    /// Get Reactor.
    virtual Reactor* getReactor() const;

    virtual int connect( SVC_HANDLER *&svcHandler, const typename PEER_CONNECTOR::PEER_ADDR &remoteAddr );
protected:
    virtual int makeSvcHandler( SVC_HANDLER *&svcHandler );
    virtual int connectSvcHandler( SVC_HANDLER *svcHandler, const typename PEER_CONNECTOR::PEER_ADDR remoteAddr );
    virtual int activateSvcHandler( SVC_HANDLER *svcHandler );

    int handleInput( int fd = INVALID_HANDLE ) override;
    int handleClose( int handle = INVALID_HANDLE ) override;

private:
    PEER_CONNECTOR mConnector;
    Reactor *mReactor;
    int mFlags;
};

} /* namespace v_1_1 */

// for splitting the template class definition into .cpp
#include "framework/v_1_1/Connector.cpp"

#endif /* FRAMEWORK_V_1_1_CONNECTOR_HPP_ */
