cmake_minimum_required(VERSION 3.9)
project(audio_player)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Quick Core Multimedia Widgets Concurrent)
qt5_add_resources(RESOURCES main.qrc)

add_executable(audio_player  ${RESOURCES}
        main.cpp
        src/AudioPlayer.cpp
        src/AudioPlayer.h
        src/AudioPlayerController.h src/AudioPlayerController.cpp
        src/SecondOrderSection.h
        filters/fdacoefs_6.h
        filters/tmwtypes.h
        src/Filter.h src/Echo.h filters/fdacoefs.h src/Effect.h src/Echo.h src/Overdrive.h)

include_directories(/usr/include/stk)
target_link_libraries(audio_player libstk.so )
qt5_use_modules(audio_player Quick Core Multimedia Concurrent Widgets)