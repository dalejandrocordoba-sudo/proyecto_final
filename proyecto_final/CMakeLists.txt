cmake_minimum_required(VERSION 3.16)

project(proyecto_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Buscar módulos de Qt necesarios (Core incluye QMap, Widgets incluye QGraphicsView)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(proyecto_final
    main.cpp

    # Encabezados (.h)
    agente.h
    balaagente.h
    dificultad.h
    enemigo.h
    entidad.h
    fisica.h
    jefebandolero.h
    juego.h
    memoria.h
    proyectil.h
    recursos.h

    # Archivos fuente (.cpp)
    agente.cpp
    balaagente.cpp
    dificultad.cpp
    enemigo.cpp
    entidad.cpp
    fisica.cpp
    jefebandolero.cpp
    juego.cpp
    memoria.cpp
    proyectil.cpp
    recursos.cpp
    objetomundo.h
    objetomundo.cpp
    pepsiman.h
    pepsiman.cpp
)

# Vincular las librerías de Qt al proyecto (esto soluciona el error de QMap)
target_link_libraries(proyecto_final PRIVATE
    Qt6::Core
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS proyecto_final
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)