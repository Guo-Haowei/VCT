#version 450 core
#extension GL_NV_gpu_shader5: enable
#extension GL_NV_shader_atomic_float: enable
#extension GL_NV_shader_atomic_fp16_vector: enable

in vec3 pass_position; // fragment world position
in vec3 pass_normal; // fragment normal
in vec2 pass_uv; // fragment normal

layout (rgba16f, binding = 0) uniform image3D u_voxel_texture;

uniform vec4 u_world; // xyz : world center; w : world size
// uniform vec3 u_world_center;
// uniform float u_world_size_half;
uniform sampler2D u_albedo;
uniform vec3 u_light_pos;

const vec3 light_position = vec3(0.0, 100.0, 2.0);

void main()
{
    vec3 N = normalize(pass_normal);
    vec3 L = normalize(light_position - pass_position);
    float diffuse = max(dot(N, L), 0.0);
    vec3 color = (diffuse) * vec3(1.0);
    // vec3 color = (diffuse) * texture(u_albedo, pass_uv);

    // write lighting information to texel
    vec3 voxel = (pass_position - u_world.xyz) / (0.5 * u_world.w); // normalize it to [-1, 1]
    voxel = 0.5 * voxel + vec3(0.5); // normalize to [0, 1]
    ivec3 dim = imageSize(u_voxel_texture);
    // float alpha = pow(1 - material.transparency, 4); // For soft shadows to work better with transparent materials.
    // ignore transparency for now
    ivec3 coord = ivec3(dim * voxel);
    f16vec4 final_color = f16vec4(color.r, color.g, color.b, 1.0);
    imageAtomicAdd(u_voxel_texture, coord, final_color);
    // imageAtomicMax(u_voxel_texture, coord, final_color);
}