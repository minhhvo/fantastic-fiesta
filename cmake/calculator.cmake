# /workspace/cmake/
# calculator.cmake

set(TARGET_PROJECT "Calculator")

add_library(MathLibrary STATIC
    MathLibrary.cpp 
)   
add_executable(${TARGET_PROJECT}
    Calculator.cpp
)

add_custom_command(TARGET ${TARGET_PROJECT} POST_BUILD
    COMMAND lib MathLibrary.obj 

)