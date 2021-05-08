add_library(math
    Vector2.cpp
    Vector3.cpp
    Vector4.cpp
    Matrix3.cpp
    Matrix4.cpp
    Plane.cpp
    Frustum.cpp
    geometries/BoxGeometry.cpp
)

if (THREE_MATH_MATH_PRECISION_DOUBLE)
    message(STATUS "three::math precision double enabled")
    target_compile_definitions(math PUBLIC -DTHREE_MATH_MATH_PRECISION_DOUBLE)
endif ()

if (THREE_MATH_DISABLE_SWIZZLE)
    message(STATUS "three::math swizzle disabled")
    target_compile_definitions(math PUBLIC -DTHREE_MATH_DISABLE_SWIZZLE)
endif ()

target_include_directories(math PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_library(three::math ALIAS math)
