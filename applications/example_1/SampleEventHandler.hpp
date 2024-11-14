/*
 * SampleEventHandler.h
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_SAMPLEEVENTHANDLER_HPP_
#define APPLICATIONS_EXAMPLE_1_SAMPLEEVENTHANDLER_HPP_

#include "v_1_0/EventHandler.hpp"
#include "v_1_0/Reactor.hpp"

namespace example_1 {

class SampleEventHandler: public v_1_0::EventHandler {
public:
	SampleEventHandler(v_1_0::Reactor *reactor = v_1_0::Reactor::getInstance());
	virtual ~SampleEventHandler();
};

} /* namespace example_1 */

#endif /* APPLICATIONS_EXAMPLE_1_SAMPLEEVENTHANDLER_HPP_ */
