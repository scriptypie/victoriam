@group vertex

#version 450

layout (location = 0) in vec3 m_Position;
layout (location = 1) in vec4 m_Color;
layout (location = 2) in vec3 m_Normal;
layout (location = 3) in vec2 m_UV;

layout (location = 0) out vec4 o_Color;

layout (push_constant) uniform MaterialData
{
    mat4 Transform;
    mat4 ModelMatrix;
    vec3 SunDirection;
} m_Data;

void main()
{
    vec4 worldPos = m_Data.Transform * vec4(m_Position, 1);
    gl_Position = worldPos;

    vec3 normalWorldSpace = normalize(mat3(m_Data.ModelMatrix) * m_Normal);
    float lightIntensity = max(dot(normalWorldSpace, m_Data.SunDirection), 0.0);

    o_Color = m_Color * lightIntensity;
}

@endgroup

@group fragment

#version 450

layout (location = 0) in vec4 m_Color;

layout (location = 0) out vec4 o_Color;

layout (push_constant) uniform MaterialData
{
    mat4 Transform;
    mat4 ModelMatrix;
    vec3 SunDirection;
} m_Data;

void main() {
    o_Color = m_Color;
}

@endgroup