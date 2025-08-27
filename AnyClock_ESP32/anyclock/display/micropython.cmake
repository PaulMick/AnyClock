add_library(usermod_display INTERFACE)

target_sources(usermod_display INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/display_driver.c
    ${CMAKE_CURRENT_LIST_DIR}/display_manager.c
    ${CMAKE_CURRENT_LIST_DIR}/display_utils.c
)

target_include_directories(usermod_display INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(usermod INTERFACE usermod_display)