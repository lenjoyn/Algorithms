add_library(Tries INTERFACE)
target_sources(Tries INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Tries/Tries.h>)
