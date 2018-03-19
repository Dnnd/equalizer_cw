cmake_minimum_required(VERSION 3.9)
project(equlizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Quick Core Multimedia Widgets Concurrent)
qt5_add_resources(RESOURCES main.qrc)

add_executable(equlizer main.cpp ${RESOURCES}
        src/filters/fdacoefs.h
        src/filters/tmwtypes.h
        src/DecodedAudioReciever.cpp
        src/DecodedAudioReciever.h
        src/DecodedAudioIterator.h
        src/DecodedAudioIterator.cpp
        src/Filter.cpp
        src/Filter.h
        src/SecondOrderSection.cpp
        src/SecondOrderSection.h
        src/AudioProcessor.cpp
        src/AudioProcessor.h src/AudioProcessor.cpp src/AudioProcessor.h)
qt5_use_modules(equlizer Quick Core Multimedia Concurrent Widgets)