cmake_minimum_required(VERSION 2.8)

PROJECT(study_framework)

set(CMAKE_CXX_COMPILER g++)
add_definitions("-Wall -std=c++11")

include_directories(${CMAKE_SOURCE_DIR})

set (example_1_client_source 
     applications/example_reactor/MainClient.cpp )
     
set (example_1_server_source 
     applications/example_reactor/MainServer.cpp
     applications/example_reactor/Acceptor.cpp
     applications/example_reactor/ServerEventHandler.cpp )
     
set (framework_v_1_0 
     framework/v_1_0/EventHandler.cpp 
     framework/v_1_0/Reactor.cpp )

set (framework_v_2_0 
     framework/v_2_0/EventHandler.cpp 
     framework/v_2_0/Reactor.cpp )
     
add_executable(example_reactor_client
  ${example_1_client_source}
)


add_executable(example_reactor_server
  ${example_1_server_source}
  ${framework_v_1_0}
)