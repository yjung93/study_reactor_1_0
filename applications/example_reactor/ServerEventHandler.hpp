/*
 * ServerEventHandler.h
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_
#define APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_

#include "framework/v_1_0/EventHandler.hpp"
#include "framework/v_1_0/Reactor.hpp"


namespace example_reactor {

class ServerEventHandler: public v_1_0::EventHandler {
public:
	ServerEventHandler(v_1_0::Reactor *reactor = v_1_0::Reactor::getInstance());
	virtual ~ServerEventHandler();

	void open();

private:
	  int handleInput( int fd = INVALID_HANDLE ) override;
};

} /* namespace example_reactor */

#endif /* APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_ */
