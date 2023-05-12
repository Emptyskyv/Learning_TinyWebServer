cmake_minimum_required(VERSION 3.24)
project(Learning_TinyWebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(lock)

add_executable(Learning_TinyWebServer
        lock/locker.h
        test.cpp main.cpp http/http_conn.h log/log.h log/block_queue.h log/log.cpp)
