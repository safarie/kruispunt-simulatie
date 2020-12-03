#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 2) uniform sampler2D texSampler;

struct Light {
    vec3 color;
    vec3 position;
    float intensity;
};

layout(binding = 3) uniform UniformBufferObject {
    Light trafficLights[82];
}ubo;

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inViewVec;
layout(location = 4) in vec3 inWorldPos;

layout(location = 0) out vec4 outFragColor;

void main() {
    vec4 color = texture(texSampler, inUV);
    vec3 fragColor = inColor * vec3(0.0, 0.0, 0.0);
    
    for(int i = 0; i < 82; ++i)
	{
        float dist = distance(ubo.trafficLights[i].position, inWorldPos);
        float watt = ubo.trafficLights[i].intensity;

        vec3 N = normalize(inNormal);
        vec3 L = normalize(ubo.trafficLights[i].position - inWorldPos);
        vec3 V = normalize(inViewVec);
        vec3 H = normalize(L + V);
   
        vec3 diffuse = inColor * ubo.trafficLights[i].color * watt * clamp(dot(N, L), 0,1) / pow(dist, 2.0);
        vec3 specular = inColor * ubo.trafficLights[i].color * vec3(watt) * pow(clamp(dot(N, H), 0,1), 5.0) / pow(dist, 2.0);

        fragColor += diffuse + specular;
    }
    
    outFragColor = color * vec4(fragColor, 1.0);
}