/*
 * Server.hpp
 *
 *  Created on: Jan 23, 2024
 *      Author: yjung93
 */

#ifndef APPLICATIONS_EXAMPLE_1_SERVER_HPP_
#define APPLICATIONS_EXAMPLE_1_SERVER_HPP_

#include "Acceptor.hpp"

namespace example_1 {

class Server: public Acceptor {
public:
	Server();
	~Server();
};

} /* namespace example_1 */

#endif /* APPLICATIONS_EXAMPLE_1_SERVER_HPP_ */
