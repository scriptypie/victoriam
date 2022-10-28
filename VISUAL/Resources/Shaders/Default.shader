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
    mat4 ViewProjection;
    vec4 Color;
} m_Data;

void main()
{
    gl_Position = m_Data.ViewProjection * m_Data.Transform * vec4(m_Position, 1);
    o_Color = m_Color;
}

@endgroup

@group fragment

#version 450

layout (location = 0) in vec4 m_Color;

layout (location = 0) out vec4 o_Color;

layout (push_constant) uniform MaterialData
{
    mat4 Transform;
    mat4 ViewProjection;
    vec3 Color;
} m_Data;

void main() {
    o_Color = m_Color;
}

@endgroup