#include <arpa/inet.h>

#include "ServiceHandler.hpp"

namespace Proactor_1_0
{

ServiceHandler::ServiceHandler()
{
}

ServiceHandler::~ServiceHandler()
{
}

void ServiceHandler::addresses( const sockaddr_in & /* remote_address */,
                                const sockaddr_in & /* local_address */ )
{
}

void ServiceHandler::act( const void * )
{
}

void ServiceHandler::open( int new_handle )
{
}

} // namespace Proactor_1_0