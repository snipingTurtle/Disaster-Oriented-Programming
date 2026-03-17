cmake_minimum_required(VERSION 3.10)
project(HallManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(HMS 
    src/main.cpp 
    src/Authorization.cpp
    src/user.cpp 
    src/complaint.cpp
    src/notice_board.cpp
    src/database_handler.cpp
<<<<<<< HEAD
    src/student.cpp
    src/person.cpp
    src/student_database.cpp
)
=======
    src/Admin.cpp
    src/AssistantProvost.cpp
    src/AssistantToProvost.cpp
    src/Provost.cpp
)
>>>>>>> e394070cd16e0dadb12d05900d1f9b2736fc83c0
