cmake_minimum_required(VERSION 3.5)


add_executable(ProjectStructure
    main.cpp
    Position.cpp
    Position.h
    Enum.h
    objectgame.h
    objectgame.cpp
    fileloader.h
    fileloader.cpp
    board.h board.cpp
    Observer.h Observable.h
    rules.h rules.cpp
    level.h level.cpp
    view.h view.cpp
    controller.cpp
    controller.h
    level_0.txt
    level_1.txt
    level_2.txt
    level_3.txt
    level_4.txt
    save.txt

)

install(TARGETS ProjectStructure
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
