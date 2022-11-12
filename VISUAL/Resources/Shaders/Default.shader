@group vertex

#version 450

layout (location = 0) in vec3 m_Position;
layout (location = 1) in vec4 m_Color;
layout (location = 2) in vec3 m_Normal;
layout (location = 3) in vec2 m_UV;

layout (location = 0) out vec4 o_Color;
layout (location = 1) out vec3 o_PosWorld;
layout (location = 2) out vec3 o_NormalWorld;

struct PointLight
{
    vec4 Position; // w is radius
    vec4 Color; // w is intensity
};

#define MAX_POINT_LIGHTS 32

layout (set = 0, binding = 0) uniform WorldConstants {
    mat4 View;
    mat4 Projection;
    vec4 SunDirection;
    vec4 Ambient; // w is intensity
    PointLight PointLights[MAX_POINT_LIGHTS];
    float Brightness;
    int ActivePLCount;
} Constants;

layout (push_constant) uniform PushData {
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

struct PointLight
{
    vec4 Position; // w is radius
    vec4 Color; // w is intensity
};

#define MAX_POINT_LIGHTS 32

layout (set = 0, binding = 0) uniform WorldConstants {
    mat4 View;
    mat4 Projection;
    vec4 SunDirection;
    vec4 Ambient; // w is intensity
    PointLight PointLights[MAX_POINT_LIGHTS];
    float Brightness;
    int ActivePLCount;
} Constants;

layout (push_constant) uniform PushData
{
    mat4 ModelMatrix;
} m_Data;

void main() {

    vec3 diffuseLight = Constants.Ambient.xyz * Constants.Ambient.w;
    vec3 surfaceNormal = normalize(m_NormalWorld);

    for (int i = 0; i < Constants.ActivePLCount; i++)
    {
        PointLight plData = Constants.PointLights[i];

        vec3 dirToLight = plData.Position.xyz - m_PosWorld;
        float atten = 1.0 / dot(dirToLight, dirToLight);
        float cosAngleIncidence = max(dot(surfaceNormal, normalize(dirToLight)), 0.0);
        vec3 intensity = plData.Color.xyz * plData.Color.w * atten;

        diffuseLight += (intensity * cosAngleIncidence) / 1.0;
    }

    o_Color = m_Color * vec4(diffuseLight, 1.0);
}

@endgroup