#include "MethodRequest.hpp"

namespace ActiveObject_1_0
{


MethodRequest::MethodRequest( unsigned long prio )
    : mPriority( prio )
{
}

unsigned long MethodRequest::priority() const
{
    return this->mPriority;
}

void MethodRequest::priority( unsigned long prio )
{
    this->mPriority = prio;
}

} //namespace ActiveObject_1_0