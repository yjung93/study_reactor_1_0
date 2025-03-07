#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

constexpr int PORT = 8080;

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    const int bufferLength = 1024;

    if ( (sock = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
    {
        std::cerr << "Socket creation error"
                  << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( PORT );

    // Convert IPv4 and IPv6 addresses from text to binary form
    if ( inet_pton( AF_INET, "127.0.0.1", &serv_addr.sin_addr ) <= 0 )
    {
        std::cerr << "Invalid address / Address not supported"
                  << std::endl;
        return -1;
    }

    if ( connect( sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr) ) < 0 )
    {
        std::cerr << "Connection Failed"
                  << std::endl;
        return -1;
    }

    bool loop = true;
    while ( loop )
    {
        std::string input;
        char buffer[bufferLength] =
        { 0 };

        std::cout << "Enter Message : ";
        std::getline( std::cin, input );

        if ( input.length() > 0 )
        {

            if ( input == "exit" )
            {
                loop = false;
            }else
            {

                send( sock, input.c_str(), input.size(), 0 );
                std::cout << "Sent : "
                          << input
                          << std::endl;

                int valRead = read( sock, buffer, bufferLength );
                if ( valRead == -1 || valRead == 0 )
                {
                    std::cout << "error : "
                              << valRead
                              << std::endl;
                    loop = false;
                }else
                {
                    std::cout << "Received: "
                              << buffer
                              << std::endl;
                }

            }
        }

    }

    close( sock );

    return 0;
}
