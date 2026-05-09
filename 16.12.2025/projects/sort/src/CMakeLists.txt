target_sources(${LIB_NAME}
    PRIVATE 
        bubble_sort.cpp
    PUBLIC 
        bubble_sort.hpp

)
target_include_directories(${LIB_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)
