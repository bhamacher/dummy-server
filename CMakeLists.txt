cmake_minimum_required(VERSION 3.1)

#set project name and language
project(dummyServer LANGUAGES CXX)

#Automoc and RCC ON. Needed in QT projects
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#C++ 11 Flag
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set project Version
set(zeramodulemanager_VERSION_MAJOR "1")
set(zeramodulemanager_VERSION_MINOR "2")
set(zeramodulemanager_VERSION_PATCH "0")

set(PROJECT_VERSION "${zeramodulemanager_VERSION_MAJOR}.${zeramodulemanager_VERSION_MINOR}.${zeramodulemanager_VERSION_PATCH}")

#Adding cmake functions like feature_summary()
include(FeatureSummary)
include(GNUInstallDirs)

#Find dependecies
find_package(Qt5 COMPONENTS Core Network Qml Concurrent CONFIG REQUIRED)
find_package(VfEvent REQUIRED)
find_package(VfComponent REQUIRED)
find_package(VfStorageHash REQUIRED)
find_package(VfTcp REQUIRED)
find_package(VfNet2 REQUIRED)
find_package(VfHelpers REQUIRED)
#find_package(VfQml REQUIRED)
find_package(VfScript REQUIRED)
find_package(VfLogger REQUIRED)
find_package(VfCryptoBridge REQUIRED)
find_Package(MeasurementModuleInterface REQUIRED)
find_Package(zeraproxy REQUIRED)
find_Package(VfCpp REQUIRED)
find_Package(VfExport REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)

#sum up project Files 
file(GLOB SOURCES
${PROJECT_SOURCE_DIR}/src/*.cpp
    )


file(GLOB HEADER
${PROJECT_SOURCE_DIR}/src/*.h
    )

file(GLOB RESOURCES 
    ${PROJECT_SOURCE_DIR}/*.qrc
    )

include_directories(
    ${PYTHON_INCLUDE_DIRS}
    )

#create executable
add_executable(dummyServer
    ${SOURCES}
    ${HEADER}
    ${RESOURCES}
    ${PLUGIN_RESOURCES}
    )


#link dependencies
target_link_libraries(dummyServer
    PRIVATE
    Qt5::Core
    Qt5::Network
    Qt5::Concurrent
    VeinMeta::VfEvent
    VeinMeta::VfComponent
    VeinMeta::VfStorageHash
    VeinMeta::VfTcp
    VeinMeta::VfNet2
    VeinMeta::VfHelpers
    VeinMeta::VfQml
    VeinMeta::VfScript
    VeinMeta::VfLogger
    VeinMeta::VfCryptoBridge
    ZeraClasses::MeasurementModuleInterface
    ZeraClasses::zeraproxy
    VeinMeta::VfCpp
    VeinMeta::VfExport

    ${PYTHON_LIBRARIES}
)	





# announce headers - target perspective
target_include_directories(dummyServer
    PUBLIC
    $<BUILD_INTERFACE:${MY_LIBRARY_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    )



#





