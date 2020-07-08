#pragma once
#include "MainRenderer.h"
#include "scene/Scene.h"
#include "application/Globals.h"
#include "base/Assertion.h"
#include <unordered_map>
#include <iostream>

namespace vct {

static std::unordered_map<const Mesh*, MeshData> g_meshLUT;
static std::unordered_map<const Material*, MaterialData> g_matLUT;

void MainRenderer::createGpuResources()
{
    Vector3 center = g_scene.boundingBox.getCenter();
    Vector3 size = g_scene.boundingBox.getSize();
    float sizeMax = std::max(size.x, std::max(size.y, size.z));
    Vector4 world(center, sizeMax);

    // create uniform buffer
    m_cameraBuffer.createAndBind(UNIFORM_BUFFER_CAMERA_SLOT);

    m_lightBuffer.createAndBind(UNIFORM_BUFFER_LIGHT_SLOT);
    m_lightBuffer.cache.position = Vector3(0.0f, 100.0f, 2.0f);
    m_lightBuffer.update();

    m_materialBuffer.createAndBind(UNIFORM_BUFFER_MATERIAL_SLOT);

    // create shader
    m_boxWireframeProgram.createFromFiles(
        DATA_DIR "shaders/box_wireframe.vert",
        DATA_DIR "shaders/box_wireframe.frag");

    m_basicProgram.createFromFiles(
        DATA_DIR "shaders/basic.vert",
        DATA_DIR "shaders/basic.frag");
    {
        m_basicProgram.use();
        m_basicProgram.setUniform(m_basicProgram.getUniformLocation("u_albedo_map"), ALBEDO_MAP_SLOT);
        m_basicProgram.stop();
    }

    m_voxelProgram.createFromFiles(
        DATA_DIR "shaders/voxel/voxelization.vert",
        DATA_DIR "shaders/voxel/voxelization.frag",
        DATA_DIR "shaders/voxel/voxelization.geom");
    {
        // set one time uniforms
        m_voxelProgram.use();
        m_voxelProgram.setUniform(m_voxelProgram.getUniformLocation("u_world"), world);
        m_voxelProgram.setUniform(m_voxelProgram.getUniformLocation("u_voxel_texture_size"), (int)VOXEL_TEXTURE_SIZE);
        m_voxelProgram.setUniform(m_voxelProgram.getUniformLocation("u_albedo_map"), ALBEDO_MAP_SLOT);
        m_voxelProgram.stop();
    }

    m_visualizeProgram.createFromFiles(
        DATA_DIR "shaders/voxel/visualization.vert",
        DATA_DIR "shaders/voxel/visualization.frag");
    {
        // set one time uniforms
        m_visualizeProgram.use();
        m_visualizeProgram.setUniform(m_visualizeProgram.getUniformLocation("u_world"), world);
        m_voxelProgram.stop();
    }

    m_voxelPostProgram.createFromFile(DATA_DIR "shaders/voxel/post.comp");

    // create box wireframe
    {
        std::vector<Vector3> points;
        std::vector<unsigned int> indices;
        three::geometry::boxWireframe(points, indices);

        glGenVertexArrays(1, &m_boxWireframe.vao);
        glGenBuffers(2, &m_boxWireframe.ebo);
        glBindVertexArray(m_boxWireframe.vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_boxWireframe.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_boxWireframe.vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * points.size(), points.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
        glEnableVertexAttribArray(0);

        m_boxWireframe.count = static_cast<unsigned int>(indices.size());
    }

    {
        std::vector<Vector3> points;
        std::vector<unsigned int> indices;
        three::geometry::box(points, indices);

        glGenVertexArrays(1, &m_box.vao);
        glGenBuffers(2, &m_box.ebo);
        glBindVertexArray(m_box.vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_box.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_box.vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * points.size(), points.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
        glEnableVertexAttribArray(0);

        m_box.count = static_cast<unsigned int>(indices.size());
    }

    /// create voxel image
    {
        Texture3DCreateInfo info;
        info.wrapS = info.wrapT = info.wrapR = GL_CLAMP_TO_BORDER;
        info.size = VOXEL_TEXTURE_SIZE;
        info.minFilter = GL_LINEAR_MIPMAP_LINEAR;
        info.magFilter = GL_NEAREST;
        info.mipLevel = VOXEL_TEXTURE_MIP_LEVEL;
        info.format = GL_RGBA16F;

        m_albedoVoxel.create3DImage(info);
        m_normalVoxel.create3DImage(info);
    }

    // load scene
    // create mesh
    for (const std::unique_ptr<Mesh>& mesh : g_scene.meshes)
    {
        MeshData data;
        glGenVertexArrays(1, &data.vao);
        glGenBuffers(4, &data.ebo);
        glBindVertexArray(data.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3u) * mesh->faces.size(), mesh->faces.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, data.vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * mesh->positions.size(), mesh->positions.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, data.vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * mesh->normals.size(), mesh->normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, data.vbos[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * mesh->uvs.size(), mesh->uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
        glEnableVertexAttribArray(2);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        data.count = 3 * static_cast<unsigned int>(mesh->faces.size());

        g_meshLUT.insert({ mesh.get(), data });
    }

    // create material
    for (const std::unique_ptr<Material>& mat : g_scene.materials)
    {
        MaterialData matData;
        if (mat->hasAlbedoMap)
        {
            matData.albedoMap.create2DImageFromFile(mat->albedoMapPath.c_str());
            matData.albedoColor = Vector4::Zero;
        }
        else
        {
            matData.albedoColor = Vector4(mat->albedoColor, 1.0f);
        }

        g_matLUT.insert({ mat.get(), matData });
    }

    glClearColor(0.3f, 0.4f, 0.3f, 1.0f);
}

void MainRenderer::visualizeVoxels()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    m_visualizeProgram.use();
    glBindVertexArray(m_box.vao);

    int mipLevel = g_UIControls.voxelMipLevel;
    m_albedoVoxel.bindImageTexture(0, mipLevel);
    GpuTexture& voxelTexture = g_UIControls.renderVoxel == 1 ? m_albedoVoxel : m_normalVoxel;

    glBindImageTexture(0, voxelTexture.getHandle(), mipLevel, GL_TRUE, 0,
                       GL_READ_ONLY, voxelTexture.getFormat());

    int size = VOXEL_TEXTURE_SIZE >> mipLevel;
    glDrawElementsInstanced(GL_TRIANGLES, m_box.count, GL_UNSIGNED_INT, 0, size * size * size);
}

void MainRenderer::renderVoxelTexture()
{
    // TODO:
    // skip rendering if scene didn't update

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glViewport(0, 0, VOXEL_TEXTURE_SIZE, VOXEL_TEXTURE_SIZE);

    m_albedoVoxel.bindImageTexture(ALBEDO_VOXEL_SLOT);
    m_normalVoxel.bindImageTexture(NORMAL_VOXEL_SLOT);
    m_voxelProgram.use();
    static GLint mLocation = m_voxelProgram.getUniformLocation("u_M");

    for (const GeometryNode& node : g_scene.geometryNodes)
    {
        m_voxelProgram.setUniform(mLocation, node.transform);
        for (const Geometry& geom : node.geometries)
        {
            const auto& meshPair = g_meshLUT.find(geom.pMesh);
            ASSERT(meshPair != g_meshLUT.end());
            const MeshData& drawData = meshPair->second;

            const auto& matPair = g_matLUT.find(geom.pMaterial);
            ASSERT(matPair != g_matLUT.end());
            const MaterialData& matData = matPair->second;

            m_materialBuffer.cache.albedoColor = matData.albedoColor;
            m_materialBuffer.update();

            glBindVertexArray(drawData.vao);
            glActiveTexture(GL_TEXTURE0 + ALBEDO_MAP_SLOT);
            matData.albedoMap.bind();

            glDrawElements(GL_TRIANGLES, drawData.count, GL_UNSIGNED_INT, 0);
        }
    }

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // post process
    m_voxelPostProgram.use();

    constexpr GLuint workGroupX = 512;
    constexpr GLuint workGroupY = 512;
    constexpr GLuint workGroupZ =
        (VOXEL_TEXTURE_SIZE * VOXEL_TEXTURE_SIZE * VOXEL_TEXTURE_SIZE) /
        (workGroupX * workGroupY);

    glDispatchCompute(workGroupX, workGroupY, workGroupZ);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    m_albedoVoxel.bind();
    m_albedoVoxel.genMipMap();
    m_normalVoxel.bind();
    m_normalVoxel.genMipMap();
}

void MainRenderer::renderSceneNoGI()
{
    m_basicProgram.use();
    static const GLint mLocation = m_basicProgram.getUniformLocation("u_M");

    for (const GeometryNode& node : g_scene.geometryNodes)
    {
        m_basicProgram.setUniform(mLocation, node.transform);
        for (const Geometry& geom : node.geometries)
        {
            const auto& meshPair = g_meshLUT.find(geom.pMesh);
            ASSERT(meshPair != g_meshLUT.end());
            const MeshData& drawData = meshPair->second;

            const auto& matPair = g_matLUT.find(geom.pMaterial);
            ASSERT(matPair != g_matLUT.end());
            const MaterialData& matData = matPair->second;

            m_materialBuffer.cache.albedoColor = matData.albedoColor;
            m_materialBuffer.update();

            glBindVertexArray(drawData.vao);
            glActiveTexture(GL_TEXTURE0 + ALBEDO_MAP_SLOT);
            matData.albedoMap.bind();

            glDrawElements(GL_TRIANGLES, drawData.count, GL_UNSIGNED_INT, 0);
        }
    }
}

void MainRenderer::renderBoundingBox()
{
    /// TODO: refactor
    m_boxWireframeProgram.use();
    static const GLint centerLocation = m_boxWireframeProgram.getUniformLocation("u_center");
    static const GLint sizeLocation = m_boxWireframeProgram.getUniformLocation("u_size");
    static const GLint colorLocation = m_boxWireframeProgram.getUniformLocation("u_color");

    glBindVertexArray(m_boxWireframe.vao);

    if (g_UIControls.showObjectBoundingBox)
    {
        m_boxWireframeProgram.setUniform(colorLocation, Vector3::UnitY);
        for (const GeometryNode& node : g_scene.geometryNodes)
        {
            for (const Geometry& geom : node.geometries)
            {
                m_boxWireframeProgram.setUniform(centerLocation, geom.boundingBox.getCenter());
                m_boxWireframeProgram.setUniform(sizeLocation, geom.boundingBox.getSize());
                glDrawElements(GL_LINES, m_boxWireframe.count, GL_UNSIGNED_INT, 0);
            }
        }
    }

    if (g_UIControls.showWorldBoundingBox)
    {
        m_boxWireframeProgram.setUniform(colorLocation, Vector3::UnitZ);
        m_boxWireframeProgram.setUniform(centerLocation, g_scene.boundingBox.getCenter());
        m_boxWireframeProgram.setUniform(sizeLocation, g_scene.boundingBox.getSize());
        glDrawElements(GL_LINES, m_boxWireframe.count, GL_UNSIGNED_INT, 0);
    }
}

void MainRenderer::render()
{
    // TODO: refactor this
    if (g_scene.dirty || g_UIControls.forceUpdateVoxelTexture)
    {
        renderVoxelTexture();
        g_scene.dirty = false;
    }


    auto extent = m_pWindow->getFrameExtent();

    if (extent.witdh * extent.height > 0)
    {
        // skip rendering if minimized
        float aspect = (float)extent.witdh / (float)extent.height;
        g_scene.camera.aspect = aspect;
        Matrix4 PV = g_scene.camera.perspective() * g_scene.camera.view();
        m_cameraBuffer.cache.PV = PV;
        m_cameraBuffer.update();

        glViewport(0, 0, extent.witdh, extent.height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDisable(GL_SCISSOR_TEST);

        if (g_UIControls.renderVoxel == 0)
            renderSceneNoGI();
        else
            visualizeVoxels();

        if (g_UIControls.showObjectBoundingBox || g_UIControls.showWorldBoundingBox)
            renderBoundingBox();
    }


    // clear voxel
    if (g_scene.dirty || g_UIControls.forceUpdateVoxelTexture)
        m_albedoVoxel.clear();
}

void MainRenderer::destroyGpuResources()
{
    m_basicProgram.destroy();
    m_boxWireframeProgram.destroy();
}

} // namespace vct
