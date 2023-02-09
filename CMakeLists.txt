cmake_minimum_required(VERSION 3.15)
project(Xml)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Xml_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Xml_SOURCE_DIR}/CMake 
  ${Xml_SOURCE_DIR}/CMake/Modules
)
include(${Xml_SOURCE_DIR}/CMake/Configure.cmake)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Xml_ExternalTarget)
    set(TargetFolders ${Xml_TargetFolders})
    set(TargetName    ${Xml_TargetName})
    set(TargetGroup   ${Xml_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    add_subdirectory(Internal/ParserBase)

    set(TargetFolders TRUE)
    set(TargetName Xml)
    set(TargetGroup )

    set(Xml_INCLUDE  ${Xml_SOURCE_DIR})
    set(Xml_LIBRARY  ${TargetName})
endif()

add_subdirectory(Xml)

if (Xml_BUILD_TEST)
    if (NOT Xml_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
