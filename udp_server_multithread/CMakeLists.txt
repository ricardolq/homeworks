add_executable(udpserver_multithread server.c)

if (WIN32)
    target_link_libraries(udpserver_multithread ws2_32)
endif()