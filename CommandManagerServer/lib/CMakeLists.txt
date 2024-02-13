cmake_minimum_required(VERSION 3.0.0)

add_library(command_manager INTERFACE)
add_library(CommandManager::CommandManager ALIAS command_manager)

add_subdirectory("handler")
add_subdirectory("processing")
add_subdirectory("parser")
add_subdirectory("socket")
add_subdirectory("protocol")
add_subdirectory("receiver")

target_link_libraries(command_manager INTERFACE  
    CommandHandlers::CommandHandlers
    CommandProcessing::CommandProcessing
    Parser::Parser
    Socket::Socket
    Protocol::Protocol
    Receiver::Receiver
)
