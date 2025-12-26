#ifndef FRAMEWORK_ACTIVE_OBJECT_1_0_EMTHOD_REQUEST_HPP_
#define FRAMEWORK_ACTIVE_OBJECT_1_0_EMTHOD_REQUEST_HPP_

namespace ActiveObject_1_0
{

class MethodRequest
{
  public:
    MethodRequest();

    virtual ~MethodRequest() = default;

    virtual int call() = 0;

    MethodRequest( const MethodRequest & ) = delete;
    void operator=( const MethodRequest & ) = delete;
    MethodRequest( MethodRequest && ) = delete;
    void operator=( MethodRequest && ) = delete;

  private:
};

} // namespace ActiveObject_1_0
#endif //FRAMEWORK_ACTIVE_OBJECT_1_0_EMTHOD_REQUEST_HPP_