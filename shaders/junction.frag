#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inViewVec;
layout(location = 4) in vec3 inLightVec;
layout(location = 5) in float inDis2Light;

layout(location = 0) out vec4 outFragColor;

void main() {
    vec4 color = texture(texSampler, inUV);
    float lightPower = 150000;
    
    vec3 N = normalize(inNormal);
    vec3 L = normalize(inLightVec);
    vec3 V = normalize(inViewVec);
    vec3 R = reflect(-L, N);
   
    vec3 ambient = inColor * vec3(0.1, 0.1, 0.1) / (inDis2Light * inDis2Light);
    vec3 diffuse = inColor * lightPower * clamp(dot(N, L), 0,1) / (inDis2Light * inDis2Light);
    vec3 specular = vec3(lightPower) * pow(clamp(dot(R, V), 0,1), 5.0) / (inDis2Light * inDis2Light);
   
    outFragColor = color * vec4(ambient + diffuse + specular, 1.0);
}