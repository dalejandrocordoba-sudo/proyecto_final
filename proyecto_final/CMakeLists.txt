cmake_minimum_required(VERSION 3.16)

project(proyecto_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(proyecto_final main.cpp
    agente.h
    memoria.h
    memoria.cpp
    enemigo.h
    enemigo.cpp
    agente.cpp
    balaagente.h
    balaagente.cpp
    proyectil.h
    proyectil.cpp
    entidad.h
    entidad.cpp
    juego.h
    juego.cpp
)

target_link_libraries(proyecto_final PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS proyecto_final
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)