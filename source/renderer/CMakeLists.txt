add_library(renderer
    RenderSystem.cpp
    GlslProgram.cpp
    GpuTexture.cpp
    RenderTarget.cpp
    MasterRenderer.cpp
    MainRenderer.cpp
    ImguiRenderer.cpp
    imgui_impl_opengl3.cpp
)

target_link_libraries(renderer PRIVATE
    glad
)

target_include_directories(renderer PRIVATE
    ${PROJECT_SOURCE_DIR}/source/
    ${PROJECT_SOURCE_DIR}/external/glad/include/
    ${PROJECT_SOURCE_DIR}/external/stb/
)

add_library(vct::renderer ALIAS renderer)
