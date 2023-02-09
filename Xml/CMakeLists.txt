set(TargetName Xml)
include(GroupSet)


set_group(Target_HDR
    Header:*.h
    Reference:*.grm
    )
set_group(Target_SRC
    Source:*.cpp
    )



include_directories(${Xml_INCLUDE} ${Utils_INCLUDE} ${ParserBase_INCLUDE})
add_library(${TargetName} ${Target_SRC} ${Target_HDR})

target_link_libraries(${TargetName} ${Utils_LIBRARY} ${ParserBase_LIBRARY})


set_target_properties(${TargetName} PROPERTIES FOLDER "${TargetGroup}")
