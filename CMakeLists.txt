# Project Needs a name ofcourse
project(train_schedule)

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

set(train_schedule_plasmoid_SRCS train_schedule.cpp schedule.cpp schedule_item.cpp station.cpp)
set(train_schedule_engine_SRCS train_schedule_engine.cpp station.cpp schedule.cpp)

kde4_add_ui_files(train_schedule_plasmoid_SRCS config.ui)

kde4_add_plugin(plasma_applet_train_schedule ${train_schedule_plasmoid_SRCS})
kde4_add_plugin(plasma_engine_train_schedule ${train_schedule_engine_SRCS})
target_link_libraries(plasma_applet_train_schedule
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
target_link_libraries(plasma_engine_train_schedule
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDECORE_LIBS} ${QT_QTNETWORK_LIBRARY})


install(TARGETS plasma_applet_train_schedule
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(TARGETS plasma_engine_train_schedule
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES train_schedule_plasmoid.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

install(FILES train_schedule_engine.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

kde4_install_icons(${ICON_INSTALL_DIR})

