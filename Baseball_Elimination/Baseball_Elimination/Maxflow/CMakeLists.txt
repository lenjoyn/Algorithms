add_library(Maxflow INTERFACE)

target_sources(Maxflow INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Maxflow/Maxflow.h>)
