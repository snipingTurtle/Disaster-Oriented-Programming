cmake_minimum_required(VERSION 3.10)
project(HallManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(HMS 
    src/main.cpp 
    src/user.cpp 
    src/complaint.cpp
    src/notice_board.cpp
    src/database_handler.cpp
    src/student.cpp
    src/person.cpp
    src/student_database.cpp
)
