
#include <sys/socket.h>
#include <netinet/in.h>

#include "NotifyPipeManager.hpp"
#include "Proactor.hpp"

namespace Proactor_1_0
{

NotifyPipeManager::NotifyPipeManager( Proactor *proactor )
    : mProactor( proactor ),
      mNotifyBuffer( 128 )
{
    if ( ::pipe( mNotifyPipe ) == -1 )
    {
        perror( "pipe failed" );
        return;
    }

    cout << "NotifyPipeManager::"
         << __FUNCTION__
         << ": "
         << " mNotifyPipe[0]="
         << mNotifyPipe[0]
         << ", mNotifyPipe[1]="
         << mNotifyPipe[1]
         << endl;

    mProactor->setNotifyHandle( mNotifyPipe[0] );
    mReadStream.open( *this, mNotifyPipe[0], 0, mProactor );
    mReadStream.read( mNotifyBuffer, mNotifyBuffer.size() );
}

NotifyPipeManager::~NotifyPipeManager()
{
}

void NotifyPipeManager::handle_read_stream( const AsynchReadStreamResult &result )
{
    cout << "NotifyPipeManager::"
         << __FUNCTION__
         << ": "
         << endl;
    mReadStream.read( mNotifyBuffer, mNotifyBuffer.size() );
}

int NotifyPipeManager::notify()
{
    cout << "NotifyPipeManager::"
         << __FUNCTION__
         << ": "
         << endl;

    // string messageToSend = "1";
    // ::send( mNotifyPipe[1], messageToSend.c_str(), messageToSend.size(), 0 );
    char byte = 1;
    ::write( mNotifyPipe[1], &byte, 1 );
    return 0;
}
} // namespace Proactor_1_0