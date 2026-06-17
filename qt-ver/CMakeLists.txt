cmake_minimum_required(VERSION 3.19)
project(task-manager-qt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

include_directories(nlohmann)

qt_standard_project_setup()


qt_add_executable(task-manager-qt
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    taskblock.h taskblock.cpp taskblock.ui
    task.h task.cpp
    taskmanager.h taskmanager.cpp
    resources.qrc
    helpwindow.h helpwindow.cpp helpwindow.ui
)

target_link_libraries(task-manager-qt
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS task-manager-qt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET task-manager-qt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})


qt_add_resources(PROJECT_RESOURCES resources.qrc)
target_sources(task-manager-qt PRIVATE ${PROJECT_RESOURCES})
