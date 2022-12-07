VERSION 1

INPUT VERTEX {
    Vector3 m_Position;
    Vector4 m_Color;
    Vector3 m_Normal;
    Vector3 m_Tangent;
    Vector3 m_Bitangent;
    Vector2 m_UV;
}

OUTPUT VERTEX {
    Vector4 o_Color;
    Vector3 o_PosWorld;
    Vector3 o_NormalWorld;
}

INPUT PIXEL {
    Vector4 m_Color;
    Vector3 m_PosWorld;
    Vector3 m_NormalWorld;
}

OUTPUT PIXEL {
    Vector4 o_Color;
}

GLOBAL STRUCT PointLight {
    Vector4 Position;
    Vector4 Color;
}

GLOBAL CONSTANT MAX_POINT_LIGHTS = 1024;

GLOBAL UNIFORM STRUCT Constants {
    Matrix4 View;
    Matrix4 Projection;
    Vector4 SunDirection;
    Vector4 Ambient;
    PointLight PointLights[MAX_POINT_LIGHTS];
    Float32 Brightness;
    Int32 ActivePLCount;
}

GLOBAL PUSH STRUCT Data {
    Matrix4 ModelMatrix;
}

PROGRAM VERTEX {

    Vector4 positionWorld = Data.ModelMatrix * Vector4(m_Position, 1);
    VERTEX_POSITION = Constants.Projection * Constants.View * positionWorld;

    o_NormalWorld = FNormalize(Matrix3(Data.ModelMatrix) * m_Normal);
    o_PosWorld = positionWorld.xyz;
    o_Color = m_Color;

} ENDPROGRAM

PROGRAM PIXEL {

    Vector3 diffuseLight = Constants.Ambient.xyz * Constants.Ambient.w;
    Vector3 surfaceNormal = FNormalize(m_NormalWorld);

    for (Int32 i = 0; i < Constants.ActivePLCount; i++)
    {
        PointLight plData = Constants.PointLights[i];

        Vector3 dirToLight = plData.Position.xyz - m_PosWorld;
        Float32 atten = 1.0 / FDot(dirToLight, dirToLight);
        Float32 cosAngleIncidence = FMax(FDot(surfaceNormal, FNormalize(dirToLight)), 0.0);
        Vector3 intensity = plData.Color.xyz * plData.Color.w * atten;

        diffuseLight += (intensity * cosAngleIncidence) / 1.0;
    }

    o_Color = m_Color * Vector4(diffuseLight, 1.0);

} ENDPROGRAM
