
set(smwidgets_files
   testsmwidgets.cpp
   testsmwidgets.h
)
add_executable(smwidgets_tst
   "${smwidgets_files}"
   )

set_target_properties(smwidgets_tst
   PROPERTIES
     CXX_STANDARD 14
     CXX_EXTENSIONS OFF
     CXX_STANDARD_REQUIRED ON
     POSITION_INDEPENDENT_CODE 1
   )

target_link_libraries(smwidgets_tst sm_widgets Qt5::Core Qt5::Gui Qt5::Widgets)
target_include_directories(smwidgets_tst PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
