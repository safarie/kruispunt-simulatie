#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightPos;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inUV;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec3 outViewVec;
layout(location = 4) out vec3 outLightVec;
layout(location = 5) out float outDis2Light;

void main() {
    mat4 modelView = ubo.view * ubo.model;
    vec4 pos = ubo.model * vec4(inPosition, 1.0);
    vec3 lPos = ubo.lightPos.xyz;

    gl_Position = ubo.proj * modelView * vec4(inPosition, 1.0);
    
    outColor = inColor;
    outUV = inUV;
	outNormal = mat3(ubo.model) * inNormal;
	outViewVec = mat3(ubo.view) * vec3(1.0);
    outLightVec = lPos - pos.xyz;
    outDis2Light = distance(lPos, pos.xyz);
}