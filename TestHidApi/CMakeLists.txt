set(qhidapi_files
   main.cpp
   mainwindow.cpp mainwindow.h
   udevmonitor.cpp udevmonitor.h
   mainwindow.ui
)
add_executable(qhidapi_tst
   "${qhidapi_files}"
   )
target_link_libraries(qhidapi_tst udev sm_widgets qhidapi Qt5::Core Qt5::Gui Qt5::Widgets)
target_include_directories(qhidapi_tst PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
