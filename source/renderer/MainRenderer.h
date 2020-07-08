#pragma once
#include "GlslProgram.h"
#include "GpuTexture.h"
#include "GpuBuffer.h"
#include "application/Window.h"

namespace vct {

struct MeshData
{
    GLuint vao          = 0;
    GLuint ebo          = 0;
    GLuint vbos[3]      = { 0, 0, 0 };
    unsigned int count  = 0;
};

struct MaterialData
{
    Vector4 albedoColor;
    GpuTexture albedoMap;
    // specular...
    // normal...
};

struct CameraBufferCache
{
    Matrix4 PV;
    // Vector3 position;
    // float padding1;
};

struct LightBufferCache
{
    Vector3 position;
    float padding;
};

struct MaterialCache
{
    Vector4 albedoColor; // if it doesn't have albedo color, then it's alpha is 0.0f
};

static_assert(sizeof(CameraBufferCache) % 16 == 0);
static_assert(sizeof(LightBufferCache) % 16 == 0);
static_assert(sizeof(MaterialCache) % 16 == 0);

class MainRenderer
{
public:
    void createGpuResources();
    void render();
    void renderBoundingBox();
    void visualizeVoxels();
    void renderSceneNoGI();
    void renderVoxelTexture();
    void destroyGpuResources();
    inline void setWindow(Window* pWindow) { m_pWindow = pWindow; }
private:
    Window* m_pWindow;

    /// shader programs
    GlslProgram m_voxelProgram;
    GlslProgram m_visualizeProgram;
    GlslProgram m_basicProgram;
    GlslProgram m_boxWireframeProgram;
    GlslProgram m_voxelPostProgram;

    /// vertex arrays
    MeshData m_boxWireframe;
    MeshData m_box; // no normals

    /// textures
    GpuTexture m_albedoVoxel;
    GpuTexture m_normalVoxel;

    /// uniform buffers
    UniformBuffer<CameraBufferCache>    m_cameraBuffer;
    UniformBuffer<LightBufferCache>     m_lightBuffer;
    UniformBuffer<MaterialCache>        m_materialBuffer;
};

} // namespace vct
