# CMakeList.txt: CMake-Projekt für "ifcexplorer_papermodel". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_library(plugin_helloWorld SHARED
        PluginHelloWorld.cpp
        PluginHelloWorld.h
        helloWorld.cpp
        helloWorld.h)

target_link_libraries(plugin_helloWorld PRIVATE ifcexplorer_plugin stdutils ifcdb)

install(FILES helloWorld.cpp helloWorld.h PluginHelloWorld.cpp PluginHelloWorld.h cmakelists-template/CMakeLists.txt DESTINATION .)