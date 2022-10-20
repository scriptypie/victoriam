@group vertex

#version 450

layout (location = 0) in vec2 m_Position;

void main()
{
    gl_Position = vec4(m_Position, 0, 1);
}

@endgroup

@group fragment

#version 450

layout (location = 0) out vec4 o_Color;

void main() {
    o_Color = vec4(0.8, 0.2, 0.3, 1.0);
}

@endgroup