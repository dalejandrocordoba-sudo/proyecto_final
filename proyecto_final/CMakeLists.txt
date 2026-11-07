cmake_minimum_required(VERSION 3.16)

project(proyecto_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(proyecto_final main.cpp
    agente.cpp
    agente.h
    memoria.h
    memoria.cpp)

include(GNUInstallDirs)
install(TARGETS proyecto_final
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
