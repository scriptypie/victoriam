@group vertex

#version 450

layout (location = 0) in vec2 m_Position;
layout (location = 1) in vec4 m_Color;

layout (location = 0) out vec4 m_OutputColor;

void main()
{
    gl_Position = vec4(m_Position, 0, 1);
    m_OutputColor = m_Color;
}

@endgroup

@group fragment

#version 450

layout (location = 0) in vec4 m_Color;

layout (location = 0) out vec4 o_Color;

void main() {
    o_Color = m_Color;
}

@endgroup