
#ifndef FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_HPP_
#define FRAMEWORK_ACTIVE_OBJECT_1_0_FUTURE_HPP_

#include <mutex>
#include <condition_variable>
#include <set>

using namespace std;

namespace ActiveObject_1_0
{

template <typename T>
class Future;
template <typename T>
class FutureRep;

template <typename T>
class FutureObserver
{
  public:
    virtual ~FutureObserver();

    virtual void update( const Future<T> &future ) = 0;

  protected:
    FutureObserver();
};

template <typename T>
class FutureRep
{
    friend class Future<T>;

  public:
    FutureRep();
    ~FutureRep();

    int cancle();
    int set( const T &r, Future<T> &caller );
    int get( T &value, unsigned long int timeout );
    int attach( FutureObserver<T> *observer, Future<T> &caller );
    int detach( FutureObserver<T> *observer );

    int ready() const;

    ::set<FutureObserver<T> *> mObserverCollection;

    mutable mutex mValueReadyMutex;
    mutable condition_variable mValueReady;
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
    int get( T &value, unsigned long int timeout = 0 ) const;

    int ready() const;
    int attach( FutureObserver<T> *observer );
    int detach( FutureObserver<T> *observer );

  private:
    shared_ptr<FutureRep<T>> mRep;
};

} // namespace ActiveObject_1_0

// for splitting the template class definition into .cpp
#include "framework/active_object/1_0/Future.cpp"

#endif //FRAMEWORK_ACTIVE_OBJECT_1_0_FUTUR_HPP_