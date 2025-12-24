#ifndef FRAMEWORK_ACTIVE_OBJECT_1_0_EMTHOD_REQUEST_HPP_
#define FRAMEWORK_ACTIVE_OBJECT_1_0_EMTHOD_REQUEST_HPP_



namespace ActiveObject_1_0
{

class MethodRequest
{
  public:
    MethodRequest( unsigned long priority = 0 );

    virtual ~MethodRequest() = default;

    unsigned long priority() const;

    void priority( unsigned long prio );

    virtual int call() = 0;

    MethodRequest( const MethodRequest & ) = delete;
    void operator=( const MethodRequest & ) = delete;
    MethodRequest( MethodRequest && ) = delete;
    void operator=( MethodRequest && ) = delete;

  private:
    unsigned long mPriority;
};

} // namespace ActiveObject_1_0
#endif //FRAMEWORK_ACTIVE_OBJECT_1_0_EMTHOD_REQUEST_HPP_