@group vertex

#version 450

const vec2 OFFSETS[6] = vec2[](
vec2(1.0, 1.0),     // 6
vec2(-1.0, 1.0),    // 5
vec2(1.0, -1.0),    // 4
vec2(1.0, -1.0),    // 3
vec2(-1.0, 1.0),    // 2
vec2(-1.0, -1.0)    // 1
);

layout (location = 0) out vec2 o_Offset;

layout (set = 0, binding = 0) uniform WorldConstants {
    mat4 View;
    mat4 Projection;
    vec4 SunDirection;
    vec4 LightPosition;
    vec4 LightColor;
    vec4 Ambient; // w is intensity
    float Brightness;
} Constants;

const float LIGHT_RADIUS = 0.1F;

void main()
{
    o_Offset = OFFSETS[gl_VertexIndex];
    vec4 inCamSpace = Constants.View * vec4(Constants.LightPosition.xyz, 1.0);
    vec4 posInCamSpace = inCamSpace + LIGHT_RADIUS * vec4(o_Offset, 0.0, 0.0);
    gl_Position = Constants.Projection * posInCamSpace;
}

@endgroup

@group fragment

#version 450

layout (location = 0) in vec2 m_Offset;
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

void main()
{
    float distance = sqrt(dot(m_Offset, m_Offset));
    if (distance >= 1.0)
        discard;
    o_Color = vec4(Constants.LightColor.xyz, 1.0);
}

@endgroup