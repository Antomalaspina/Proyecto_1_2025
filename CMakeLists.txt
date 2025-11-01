cmake_minimum_required(VERSION 3.19)
project(Space_Invaders LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Space_Invaders
    main.cpp
    gamewidget.h gamewidget.cpp
    gamelogic.h gamelogic.cpp
    dibujable_abstracto.h dibujable_abstracto.cpp
    barrera.h barrera.cpp
    nave.h nave.cpp
    alien.h alien.cpp
    calamar.h calamar.cpp
    cangrejo.h cangrejo.cpp
    pulpo.h pulpo.cpp
    proyectil.h proyectil.cpp
    escenario.h escenario.cpp
)

target_link_libraries(Space_Invaders
    PRIVATE
        Qt::Core
)
target_link_libraries(Space_Invaders PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS Space_Invaders
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
