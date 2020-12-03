#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inUV;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec3 outViewVec;
layout(location = 4) out vec3 outWorldPos;

void main() {
    vec4 worldPos = ubo.model * vec4(inPosition, 1.0);
    
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    
    outColor = inColor;
    outUV = inUV;
	outNormal = mat3(ubo.model) * inNormal;
    outViewVec = ubo.view[3].xyz - worldPos.xyz;
    outWorldPos = worldPos.xyz;
}