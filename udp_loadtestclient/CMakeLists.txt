add_executable(loadtestclient client.c)

if (WIN32)
    target_link_libraries(loadtestclient ws2_32)
endif()