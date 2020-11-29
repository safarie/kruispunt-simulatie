#version 450
#extension GL_ARB_separate_shader_objects : enable

struct Light {
    vec3 color;
    vec3 position;
    float intensity;
};

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    Light sun;
} ubo;

layout(binding = 1) uniform DynamicUniformBufferObject {
    mat4 model;
} dubo;

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
layout(location = 6) out float outSunPower;

void main() {
    mat4 modelView = ubo.view * dubo.model;
    vec4 pos = dubo.model * vec4(inPosition, 1.0);
    vec3 lPos = ubo.sun.position;

    gl_Position = ubo.proj * modelView * vec4(inPosition, 1.0);
    
    outColor = ubo.sun.color * inColor;
    outUV = inUV;
	outNormal = mat3(dubo.model) * inNormal;
	outViewVec = ubo.view[3].xyz - pos.xyz;
    outLightVec = lPos - pos.xyz;
    outDis2Light = distance(lPos, pos.xyz);
    outSunPower = ubo.sun.intensity;

    // vec4 worldPos = dubo.model * vec4(inPosition, 1.0);
    //
    // gl_Position = ubo.proj * ubo.view * dubo.model * vec4(inPosition, 1.0);
    //
    // outColor = inColor;
    // outUV = inUV;
	// outNormal = mat3(dubo.model) * inNormal;
    // outViewVec = ubo.view[3].xyz - worldPos.xyz;
    // outWorldPos = worldPos;
}