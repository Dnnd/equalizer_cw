cmake_minimum_required(VERSION 3.9)
project(audio_player)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Quick Core Multimedia Widgets Concurrent Charts)
qt5_add_resources(RESOURCES main.qrc)

add_executable(audio_player
        ${RESOURCES}
        main.cpp
        src/AudioPlayer.cpp
        src/AudioPlayer.h
        src/AudioPlayerController.h src/AudioPlayerController.cpp
        src/SecondOrderSection.h
        src/Filter.h src/Echo.h filters/fdacoefs.h src/Effect.h src/Echo.h src/Overdrive.h src/AudioSpectre.cpp src/AudioSpectre.h
        src/kiss_fft.h src/kiss_fftr.c src/kiss_fftr.h src/_kiss_fft_guts.h src/kiss_fft.c)

include_directories(/usr/include/stk)
target_link_libraries(audio_player libstk.so Qt5::Quick Qt5::Core Qt5::Concurrent Qt5::Widgets Qt5::Charts)