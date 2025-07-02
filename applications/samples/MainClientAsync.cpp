#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

using namespace std;

constexpr int PORT = 8080;
constexpr char SERVER_IP[] = "127.0.0.1";
constexpr int CONNECT_TIMEOUT_SEC = 5;

int main()
{
    int sock = socket( AF_INET, SOCK_STREAM, 0 );
    if ( sock < 0 )
    {
        std::perror( "socket() failed" );
        return 1;
    }

    // 1. Make socket non-blocking
    int flags = fcntl( sock, F_GETFL, 0 );
    if ( flags < 0 )
    {
        std::perror( "fcntl(F_GETFL)" );
        close( sock );
        return 1;
    }
    if ( fcntl( sock, F_SETFL, flags | O_NONBLOCK ) < 0 )
    {
        std::perror( "fcntl(F_SETFL)" );
        close( sock );
        return 1;
    }

    cout
    << "SockStream::"
    << __FUNCTION__
    << ": 0.2 "
    << " fcntl value =0x"
    << std::hex
    << fcntl( sock, F_GETFL, 0 )
    << endl;

    // 2. Initiate connect (will return EINPROGRESS)
    struct sockaddr_in serv_addr;
    std::memset( &serv_addr, 0, sizeof(serv_addr) );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( PORT );
    if ( inet_pton( AF_INET, SERVER_IP, &serv_addr.sin_addr ) <= 0 )
    {
        std::cerr << "Invalid address\n";
        close( sock );
        return 1;
    }

    int res = connect( sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr) );
    if ( res < 0 && errno != EINPROGRESS )
    {
        std::perror( "connect()" );
        close( sock );
        return 1;
    }



    // 3. Use select() to wait for the socket to be writable
    fd_set writefds;
    FD_ZERO( &writefds );
    FD_SET( sock, &writefds );
    struct timeval tv;
    tv.tv_sec = CONNECT_TIMEOUT_SEC;
    tv.tv_usec = 0;

    std::cout << "Waiting up to "
              << CONNECT_TIMEOUT_SEC
              << " seconds for connection...\n";

    int sel = select( sock + 1, nullptr, &writefds, nullptr, &tv );
    if ( sel < 0 )
    {
        std::perror( "select()" );
        close( sock );
        return 1;
    }else if ( sel == 0 )
    {
        std::cerr << "Connection timed out\n";
        close( sock );
        return 1;
    }

    // 4. Check the socket for errors
    int so_error = 0;
    socklen_t len = sizeof(so_error);
    if ( getsockopt( sock, SOL_SOCKET, SO_ERROR, &so_error, &len ) < 0 )
    {
        std::perror( "getsockopt()" );
        close( sock );
        return 1;
    }
    if ( so_error != 0 )
    {
        std::cerr << "connect failed: "
                  << std::strerror( so_error )
                  << "\n";
        close( sock );
        return 1;
    }

    std::cout << "Connected successfully!\n";

    // 5. Switch back to blocking mode for simplicity (optional)
    fcntl( sock, F_SETFL, flags );

    // 6. Send and receive
    const std::string message = "Hello from non-blocking client";
    if ( send( sock, message.c_str(), message.size(), 0 ) < 0 )
    {
        std::perror( "send()" );
        close( sock );
        return 1;
    }
    std::cout << "Message sent, waiting for reply...\n";

    char buffer[1024];
    int n = recv( sock, buffer, sizeof(buffer) - 1, 0 );
    if ( n < 0 )
    {
        std::perror( "recv()" );
    }else if ( n == 0 )
    {
        std::cout << "Server closed connection\n";
    }else
    {
        buffer[n] = '\0';
        std::cout << "Received: "
                  << buffer
                  << "\n";
    }

    close( sock );
    return 0;
}
