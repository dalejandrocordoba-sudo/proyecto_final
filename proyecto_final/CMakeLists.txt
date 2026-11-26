cmake_minimum_required(VERSION 3.16)

project(proyecto_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Módulos de Qt necesarios
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(proyecto_final
    main.cpp

    # Encabezados (.h)
    agente.h
    animacion.h
    balaagente.h
    dificultad.h
    enemigo.h
    entidad.h
    fisica.h
    fondoparallax.h
    jefebandolero.h
    juego.h
    memoria.h
    objetomundo.h
    pepsiman.h
    proyectil.h
    recursos.h

    # Archivos fuente (.cpp)
    agente.cpp
    animacion.cpp
    balaagente.cpp
    dificultad.cpp
    enemigo.cpp
    entidad.cpp
    fisica.cpp
    fondoparallax.cpp
    jefebandolero.cpp
    juego.cpp
    memoria.cpp
    objetomundo.cpp
    pepsiman.cpp
    proyectil.cpp
    recursos.cpp
)

# Incrustar imágenes en la raíz "/" (para rutas como ":/pepsiman_pedalear_A_01.png")
file(GLOB_RECURSE IMAGENES_RECURSOS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "recursos/*")
qt_add_resources(proyecto_final "recursos_juego"
    PREFIX "/"
    BASE "recursos"
    FILES ${IMAGENES_RECURSOS}
)

# Copiar la carpeta recursos al directorio build (para rutas relativas como "recursos/...")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/recursos DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Vincular las librerías de Qt al proyecto
target_link_libraries(proyecto_final PRIVATE
    Qt6::Core
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS proyecto_final
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)