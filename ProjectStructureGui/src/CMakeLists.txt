cmake_minimum_required(VERSION 3.5)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(ProjectStructure
    main.cpp
    position.cpp
    position.h
    Enum.h
    objectgame.h
    objectgame.cpp
    fileloader.h
    fileloader.cpp
    board.h
    board.cpp
    observer.h
    observable.h
    rules.h
    rules.cpp
    level.h
    level.cpp
    view.h view.cpp
    controller.cpp controller.h
    controllergui.h controllergui.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    gamegrid.h gamegrid.cpp
    sprite.qrc
    level_0.txt
    level_1.txt
    level_2.txt
    level_3.txt
    level_4.txt
    save.txt
)

# Liez les bibliothèques Qt à votre exécutable
target_link_libraries(ProjectStructure PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ProjectStructure
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

