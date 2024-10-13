set(ExeName "qtKeyboardTest")

add_executable(${ExeName} main.cpp)
target_link_libraries(${ExeName} Qt5::Widgets)
