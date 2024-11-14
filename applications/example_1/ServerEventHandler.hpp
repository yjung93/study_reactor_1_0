/*
 * ServerEventHandler.h
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_
#define APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_

#include "v_1_0/EventHandler.hpp"
#include "v_1_0/Reactor.hpp"


namespace example_1 {

class ServerEventHandler: public v_1_0::EventHandler {
public:
	ServerEventHandler(v_1_0::Reactor *reactor = v_1_0::Reactor::getInstance());
	virtual ~ServerEventHandler();

	void open();
};

} /* namespace example_1 */

#endif /* APPLICATIONS_EXAMPLE_1_ServerEventHandler_HPP_ */
