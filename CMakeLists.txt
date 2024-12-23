cmake_minimum_required(VERSION 2.8)

PROJECT(study_framework)

set(CMAKE_CXX_COMPILER g++)
add_definitions("-Wall -std=c++11")

include_directories(${CMAKE_SOURCE_DIR})

set (example_1_client_source 
     applications/example_1/MainClient.cpp 
     applications/example_1/Client.cpp)
     
set (example_1_server_source 
     applications/example_1/MainServer.cpp
     applications/example_1/Acceptor.cpp
     applications/example_1/ServerEventHandler.cpp )
     
set (framework_source_v_1_0 
     v_1_0/EventHandler.cpp 
     v_1_0/Reactor.cpp )

add_executable(Example1_Client
  ${example_1_client_source}
  ${framework_source_v_1_0}
)


add_executable(Example1_Server
  ${example_1_server_source}
  ${framework_source_v_1_0}
)