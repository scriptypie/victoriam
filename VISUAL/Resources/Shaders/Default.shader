@group vertex

#version 450

layout (location = 0) in vec3 m_Position;
layout (location = 1) in vec4 m_Color;
layout (location = 2) in vec3 m_Normal;
layout (location = 3) in vec2 m_UV;

layout (location = 0) out vec4 o_Color;

layout (set = 0, binding = 0) uniform WorldConstants {
    mat4 ProjectionView;
    vec4 SunDirection;
    float Ambient;
    float Brightness;
} Constants;

layout (push_constant) uniform MaterialData {
    mat4 ModelMatrix;
} m_Data;

void main()
{

    gl_Position = Constants.ProjectionView * m_Data.ModelMatrix * vec4(m_Position, 1);

    vec3 normalWorldSpace = normalize(mat3(m_Data.ModelMatrix) * m_Normal);
    float lightIntensity = min(Constants.Ambient + max(dot(normalWorldSpace, vec3(Constants.SunDirection)), 0.0), Constants.Brightness);

    o_Color = m_Color * lightIntensity;
}

@endgroup

@group fragment

#version 450

layout (location = 0) in vec4 m_Color;

layout (location = 0) out vec4 o_Color;

layout (push_constant) uniform MaterialData
{
    mat4 ModelMatrix;
} m_Data;

void main() {
    o_Color = m_Color;
}

@endgroup