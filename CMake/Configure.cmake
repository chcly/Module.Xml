# -----------------------------------------------------------------------------
#
#   Copyright (c) Charles Carley.
#
#   This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
#   Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
# ------------------------------------------------------------------------------
include(GitUpdate)
if (NOT GitUpdate_SUCCESS)
    return()
endif()

include(StaticRuntime)
include(ExternalTarget)
include(GTestUtils)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(Xml_BUILD_TEST          "Build the unit test program." ON)
option(Xml_AUTO_RUN_TEST       "Automatically run the test program." OFF)
option(Xml_USE_STATIC_RUNTIME  "Build with the MultiThreaded(Debug) runtime library." ON)
option(Xml_JUST_MY_CODE        "Enable the /JMC flag" ON)
option(Xml_OPEN_MP             "Enable low-level fill and copy using OpenMP" ON)

if (Xml_USE_STATIC_RUNTIME)
    set_static_runtime()
else()
    set_dynamic_runtime()
endif()

configure_gtest(${Xml_SOURCE_DIR}/Test/googletest 
                ${Xml_SOURCE_DIR}/Test/googletest/googletest/include)

DefineExternalTargetEx(
    Utils Extern
    ${Xml_SOURCE_DIR}/Internal/Utils 
    ${Xml_SOURCE_DIR}/Internal/Utils
    ${Xml_BUILD_TEST}
    ${Xml_AUTO_RUN_TEST}
)
DefineExternalTargetEx(
    ParserBase Extern
    ${Xml_SOURCE_DIR}/Internal/ParserBase
    ${Xml_SOURCE_DIR}/Internal/ParserBase
    ${Xml_BUILD_TEST}
    ${Xml_AUTO_RUN_TEST}
)



set(ExtraFlags )
if (MSVC)
    # globally disable scoped enum warnings
    set(ExtraFlags "${ExtraFlags} /wd26812")
    
    
    set(ExtraFlags "${ExtraFlags} /W3")


    if (Xml_JUST_MY_CODE)
        # Enable just my code...
        set(ExtraFlags "${ExtraFlags} /JMC")
    endif ()

    set(ExtraFlags "${ExtraFlags} /fp:precise")
    set(ExtraFlags "${ExtraFlags} /fp:except")

    if (Xml_OPEN_MP)
        add_definitions(-DRT_OPEN_MP=1)
        set(ExtraFlags "${ExtraFlags} /openmp")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ExtraFlags}")

else ()
    set(ExtraFlags "${ExtraFlags} -Os")
    set(ExtraFlags "${ExtraFlags} -O3")
    set(ExtraFlags "${ExtraFlags} -fPIC")

    if (Xml_OPEN_MP)
        add_definitions(-DRT_OPEN_MP=1)
        set(ExtraFlags "${ExtraFlags} -fopenmp")
    endif()
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ExtraFlags}")
endif ()

message(STATUS "Extra global flags: ${ExtraFlags}")
message(STATUS "Global flags: ${CMAKE_CXX_FLAGS}")

set(Configure_SUCCEEDED TRUE)