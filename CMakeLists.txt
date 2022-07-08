cmake_minimum_required(VERSION 3.1)

project(main)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_singleton
    test_singleton.cpp
    )

add_executable(test_observer
    test_observer.cpp
    )

add_executable(test_visitor
    test_visitor.cpp
    )

add_executable(test_command
    test_command.cpp
    )

add_executable(test_object_pool
    test_object_pool.cpp
    )
