/*
 * HalfAsyncHandler.h
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_HalfAsyncHandler_HPP_
#define APPLICATIONS_EXAMPLE_1_HalfAsyncHandler_HPP_

#include <memory>

#include "framework/reactor/1_0/EventHandler.hpp"
#include "framework/reactor/1_0/Reactor.hpp"
#include "HalfSyncHandler.hpp"

namespace  ExHalfSyncAsync {

class Acceptor;

class HalfAsyncHandler: public Reactor_1_0::EventHandler {
public:
	HalfAsyncHandler(Reactor_1_0::Reactor *reactor, Acceptor &owner);
	virtual ~HalfAsyncHandler();

	void open();

private:
	  int handleInput( int fd = INVALID_HANDLE ) override;

	  Acceptor *mOwner;
	  std::unique_ptr<HalfSyncHandler> mHalfSyncHandler;
};

} /* namespace  ExHalfSyncAsync */

#endif /* APPLICATIONS_EXAMPLE_1_HalfAsyncHandler_HPP_ */
