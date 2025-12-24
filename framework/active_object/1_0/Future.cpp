
#ifndef FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_CPP_
#define FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_CPP_

#include "Future.hpp"

namespace ActiveObject_1_0
{

template <typename T>
FutureRep<T>::FutureRep()
    : mValue( nullptr )
{
}
template <typename T>
FutureRep<T>::~FutureRep()
{
    if ( this->mValue != nullptr )
    {
        delete this->mValue;
    }
}

template <typename T>
int FutureRep<T>::set( const T &r, Future<T> &caller )
{
    // TBD

    return 0;
}

template <typename T>
int FutureRep<T>::set( const T &r )
{
    if ( this->mValue == nullptr )
    {
        unique_lock<std::mutex> lock( mValueReadyMutex );
        this->mValue = new T( r );
        this->mValueReady.notify_all();
    }
    return 0;
}

template <typename T>
int FutureRep<T>::get( T &value, unsigned long int timeout ) 
{
    if ( this->mValue == nullptr )
    {
        unique_lock<mutex> lock( this->mValueReadyMutex );
        mValueReady.wait_for( lock,
                              chrono::seconds( timeout ),
                              [this]
                              { return ( this->mValue != nullptr ); } );
    }

    value = *this->mValue;

    return 0;
}
template <typename T>
int FutureRep<T>::ready() const
{
    return ( this->mValue != nullptr ) ? 0 : -1;
}

template <typename T>
Future<T>::Future()
    : mRep( make_shared<FutureRep<T>>() )
{
}

template <typename T>
Future<T>::~Future()
{
}

template <typename T>
int Future<T>::cancle()
{
    this->mRep = make_shared<FutureRep<T>>();
    return 0;
}

template <typename T>
int Future<T>::set( const T &r )
{
    return this->mRep->set( r );
}

template <typename T>
int Future<T>::get( T &value, unsigned long int timeout )
{
    return this->mRep->get( value, timeout );
}

template <typename T>
int Future<T>::ready() const
{
    return this->mRep->ready();
}
} //namespace ActiveObject_1_0

#endif //FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_CPP_