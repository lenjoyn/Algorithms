add_library(BoggleBoard INTERFACE)
target_link_libraries(BoggleBoard INTERFACE Tries)
target_sources(BoggleBoard INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/BoggleBoard/BoggleBoard.h>)
