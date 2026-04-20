cmake_minimum_required(VERSION 3.21)
project(QtHello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(APP_SOURCES
    src/main.cpp
    src/model/board.h
    src/model/game.h
    src/model/square.h

    src/model/MessageModel.cpp
    src/model/MessageModel.h
    
    src/controller/AppController.cpp
    src/controller/AppController.h

    src/view/MainWindow.cpp
    src/view/MainWindow.h
)

add_executable(app ${APP_SOURCES})

target_include_directories(app PRIVATE src)

target_link_libraries(app PRIVATE Qt6::Widgets)