@group vertex

#version 450

vec2 m_Positions[3] = vec2[](
vec2( 0.0, -0.5),
vec2( 0.5,  0.5),
vec2(-0.5,  0.5)
);

void main()
{
    gl_Position = vec4(m_Positions[gl_VertexIndex], 0, 1);
}

@endgroup

@group fragment

#version 450

layout (location = 0) out vec4 o_Color;

void main() {
    o_Color = vec4(0.8, 0.2, 0.3, 1.0);
}

@endgroup