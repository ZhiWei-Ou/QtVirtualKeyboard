
set(PluginName "qtkeyboard")
set(PluginVersion "0.0.1")

set(WorkSpace
    ${CMAKE_CURRENT_SOURCE_DIR}/entry
    ${CMAKE_CURRENT_SOURCE_DIR}/infra
    ${CMAKE_CURRENT_SOURCE_DIR}/infra/en
    ${CMAKE_CURRENT_SOURCE_DIR}/infra/symbol
    ${CMAKE_CURRENT_SOURCE_DIR}/infra/refact
    ${CMAKE_CURRENT_SOURCE_DIR}/keyboards
)

set(SourceEntrys)

foreach(WorkSpacePath ${WorkSpace})
    file(GLOB_RECURSE aux
        "${WorkSpacePath}/*.cpp"
    )
    list(APPEND SourceEntrys ${aux})
endforeach()

add_library(${PluginName} SHARED
    ${SourceEntrys}
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/assets.qrc
)
target_include_directories(${PluginName}
    PRIVATE
    ${WorkSpace}
)
target_link_libraries(${PluginName}
    PRIVATE
    Qt5::GuiPrivate Qt5::Core Qt5::Widgets Qt5::Svg
)
set_target_properties(${PluginName} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/dist/platforminputcontexts"
)
