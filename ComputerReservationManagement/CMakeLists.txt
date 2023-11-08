cmake_minimum_required(VERSION 3.26)
project(ComputerReservationManagement)

set(CMAKE_CXX_STANDARD 17)

add_executable(ComputerReservationManagement main.cpp
        Identity.h
        student.h
        student.cpp
        teacher.h
        teacher.cpp
        manager.h
        manager.cpp
        globalFile.h
        Clear.cpp
        Clear.h
        computerRoom.h
        orderFile.h
        orderFile.cpp)
