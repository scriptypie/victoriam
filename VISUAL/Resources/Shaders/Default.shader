@group vertex

#version 450

layout (location = 0) in vec3 m_Position;
layout (location = 1) in vec4 m_Color;
layout (location = 2) in vec3 m_Normal;
layout (location = 3) in vec2 m_UV;

layout (location = 0) out vec4 o_Color;
layout (location = 1) out vec3 o_PosWorld;
layout (location = 2) out vec3 o_NormalWorld;

layout (set = 0, binding = 0) uniform WorldConstants {
    mat4 View;
    mat4 Projection;
    vec4 SunDirection;
    vec4 LightPosition;
    vec4 LightColor;
    vec4 Ambient; // w is intensity
    float Brightness;
} Constants;

layout (push_constant) uniform MaterialData {
    mat4 ModelMatrix;
} m_Data;

void main()
{
    vec4 positionWorld = m_Data.ModelMatrix * vec4(m_Position, 1);;
    gl_Position = Constants.Projection * Constants.View * positionWorld;

    o_NormalWorld = normalize(mat3(m_Data.ModelMatrix) * m_Normal);
    o_PosWorld = positionWorld.xyz;
    o_Color = m_Color;
}

@endgroup

@group fragment

#version 450

layout (location = 0) in vec4 m_Color;
layout (location = 1) in vec3 m_PosWorld;
layout (location = 2) in vec3 m_NormalWorld;

layout (location = 0) out vec4 o_Color;

layout (set = 0, binding = 0) uniform WorldConstants {
    mat4 View;
    mat4 Projection;
    vec4 SunDirection;
    vec4 LightPosition;
    vec4 LightColor;
    vec4 Ambient; // w is intensity
    float Brightness;
} Constants;

layout (push_constant) uniform MaterialData
{
    mat4 ModelMatrix;
} m_Data;

void main() {
    vec3 dirToLight = Constants.LightPosition.xyz - m_PosWorld;
    float atten = 1.0 / dot(dirToLight, dirToLight);

    vec3 lightColor = Constants.LightColor.xyz * Constants.LightColor.w * atten;
    vec3 ambientLight = Constants.Ambient.xyz * Constants.Ambient.w;
    vec3 diffuseLight = lightColor * max(dot(normalize(m_NormalWorld), normalize(dirToLight)), 0.0);

    o_Color = m_Color * vec4(diffuseLight + ambientLight, 1.0);
}

@endgroup