@group vertex

#version 450

layout (location = 0) in vec2 m_Position;
layout (location = 1) in vec4 m_Color;

layout (push_constant) uniform MaterialData
{
    layout(row_major) mat4 Transform;
    vec2 Offset;
    vec3 Color;
} m_Data;

void main()
{
    gl_Position = vec4(mat2(m_Data.Transform) * m_Position + m_Data.Offset, 0, 1);
}

@endgroup

@group fragment

#version 450

layout (location = 0) out vec4 o_Color;

layout (push_constant) uniform MaterialData
{
    layout(row_major) mat4 Transform;
    vec2 Offset;
    vec3 Color;
} m_Data;

void main() {
    o_Color = vec4(m_Data.Color, 1.0);
}

@endgroup