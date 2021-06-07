cmake_minimum_required(VERSION 3.19)
project(ProcessManager)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(ProcessManager main.cpp src/User.cpp include/User.h src/Program.cpp include/Program.h src/Terminal.cpp include/Terminal.h src/Admin.cpp include/Admin.h src/Utils.cpp include/Utils.h src/UtilMethods.cpp include/UtilMethods.h src/UI.cpp include/UI.h include/stdafx.h)