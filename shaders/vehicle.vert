#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightPosition;
} ubo;

layout(binding = 1) uniform DynamicUniformBufferObject {
    mat4 model;
} dubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 fragViewVec;
layout(location = 4) out vec3 fragLightVec;

void main() {   
    mat4 modelView = ubo.view * ubo.model;
    
    gl_Position = ubo.proj * ubo.view * dubo.model * vec4(inPosition.xyz, 1.0);
    vec4 worldPos = dubo.model * vec4(inPosition, 1.0);

    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragNormal = mat3(dubo.model) * inNormal;
    fragViewVec = (ubo.view * worldPos).xyz;
    fragLightVec = ubo.lightPosition - vec3(worldPos);
}