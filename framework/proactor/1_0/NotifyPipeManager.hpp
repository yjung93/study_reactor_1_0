#ifndef PROACTOR_1_0_NOTIFY_PIPE_MANAGER_HPP_
#define PROACTOR_1_0_NOTIFY_PIPE_MANAGER_HPP_

#include <vector>
#include "Handler.hpp"
#include "AsynchReadStream.hpp"

using namespace std;

namespace Proactor_1_0
{

class Proactor;
class NotifyPipeManager : public Handler
{
  public:
    NotifyPipeManager( Proactor *proactor );
    ~NotifyPipeManager();

    void handleReadStream( const AsynchReadStreamResult &result ) override;
    int notify();

  private:
    NotifyPipeManager() {};

    Proactor *mProactor;
    int mNotifyPipe[2];
    vector<uint8_t> mNotifyBuffer;
    AsynchReadStream mReadStream;
};

} // namespace Proactor_1_0
#endif // PROACTOR_1_0_NOTIFY_PIPE_MANAGER_HPP_