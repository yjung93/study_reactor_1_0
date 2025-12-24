
#ifndef FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_HPP_
#define FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_HPP_

#include <mutex>
#include <condition_variable>

using namespace std;

namespace ActiveObject_1_0
{

template <typename T>
class Future;
template <typename T>
class FutureRep;

template <typename T>
class FutureRep
{
    friend class Future<T>;

  public:
    FutureRep();
    ~FutureRep();

    int cancle();
    int set( const T &r, Future<T> &caller );
    int set( const T &r );
    int get( T &value, unsigned long int timeout );

    int ready() const;

    mutex mValueReadyMutex;
    condition_variable mValueReady;
    T *mValue;

  private:
  protected:
};

template <typename T>
class Future
{
  public:
    Future();
    ~Future();

    int cancle();
    int set( const T &r );
    int get( T &value, unsigned long int timeout );

    int ready() const;

  private:
    shared_ptr<FutureRep<T>> mRep;
};

} // namespace ActiveObject_1_0

// for splitting the template class definition into .cpp
#include "framework/active_object/1_0/Future.cpp"

#endif //FRAMEWORK_ACTIVE_OBJECT_1_0_FUTUR_HPP_