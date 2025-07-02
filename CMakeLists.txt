cmake_minimum_required(VERSION 2.8)

PROJECT(study_framework)

set(CMAKE_CXX_COMPILER g++)
add_definitions("-Wall -std=c++11")

include_directories(${CMAKE_SOURCE_DIR})

set (framework_v_1_0 
     framework/v_1_0/EventHandler.cpp 
     framework/v_1_0/Reactor.cpp )
     
set (framework_v_1_1_lib
     framework/v_1_1/Acceptor.cpp 
     framework/v_1_1/EventHandler.cpp 
     framework/v_1_1/Reactor.cpp
     framework/v_1_1/Connector.cpp
     framework/v_1_1/ServiceHandler.cpp 
     framework/v_1_1/SockAcceptor.cpp 
     framework/v_1_1/SockConnector.cpp 
     framework/v_1_1/SockStream.cpp )
     
set (lib_framework_reactor_1_0
     framework/reactor/1_0/EventHandler.cpp 
     framework/reactor/1_0/Reactor.cpp )
     
set (lib_framework_acceptor_connector_1_0
     framework/acceptor_connector/1_0/Acceptor.cpp 
     framework/acceptor_connector/1_0/Connector.cpp
     framework/acceptor_connector/1_0/ServiceHandler.cpp 
     framework/acceptor_connector/1_0/SockAcceptor.cpp 
     framework/acceptor_connector/1_0/SockConnector.cpp 
     framework/acceptor_connector/1_0/SockStream.cpp )


set (example_1_client_source 
     applications/example_reactor/MainClient.cpp )
     
set (example_1_server_source 
     applications/example_reactor/MainServer.cpp
     applications/example_reactor/Acceptor.cpp
     applications/example_reactor/ServerEventHandler.cpp )
     
set (ex_acc_con_server_lib
     applications/example_acceptor_connector/MainServer.cpp
     applications/example_acceptor_connector/AcceptorImpl.cpp
     applications/example_acceptor_connector/InputHandler.cpp)

set (ex_acc_con_client_lib
     applications/example_acceptor_connector/MainClient.cpp
     applications/example_acceptor_connector/ConnectorImpl.cpp
     applications/example_acceptor_connector/OutputHandler.cpp 
     applications/example_acceptor_connector/Client.cpp)
         
add_executable(example_reactor_client
  ${example_1_client_source}
)

add_executable(example_reactor_server
  ${example_1_server_source}
  ${lib_framework_reactor_1_0}
)
 
add_executable(ex_acc_con_client_1
  ${ex_acc_con_client_lib}
  ${lib_framework_acceptor_connector_1_0}
  ${lib_framework_reactor_1_0}
)

add_executable(ex_acc_con_server_1
  ${ex_acc_con_server_lib}
  ${lib_framework_acceptor_connector_1_0}
  ${lib_framework_reactor_1_0}
)


 