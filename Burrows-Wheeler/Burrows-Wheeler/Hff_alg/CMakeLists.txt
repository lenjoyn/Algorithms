add_library(Hff_alg INTERFACE)
target_sources(Hff_alg INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Hff_alg/Hff_alg.h>)
