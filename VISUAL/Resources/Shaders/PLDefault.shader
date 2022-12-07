VERSION 1

OUTPUT VERTEX {
    Vector2 o_Offset;
}

INPUT PIXEL {
    Vector2 m_Offset;
}

OUTPUT PIXEL {
    Vector4 o_Color;
}

VERTEX Vector2 OFFSETS[6] {
    Vector2[](
    Vector2(1.0, 1.0),
    Vector2(-1.0, 1.0),
    Vector2(1.0, -1.0),
    Vector2(1.0, -1.0),
    Vector2(-1.0, 1.0),
    Vector2(-1.0, -1.0)
    )
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
    Vector4 Position;
    Vector4 Color;
}

PROGRAM VERTEX {

    o_Offset = OFFSETS[gl_VertexIndex];
    Vector4 inCamSpace = Constants.View * Vector4(Data.Position.xyz, 1.0);
    Vector4 posInCamSpace = inCamSpace + Data.Position.w * Vector4(o_Offset, 0.0, 0.0);
    gl_Position = Constants.Projection * posInCamSpace;

} ENDPROGRAM

PROGRAM PIXEL {

    Float32 distance = FSqrt(FDot(m_Offset, m_Offset));
    if (distance >= 1.0)
        discard;
    o_Color = Vector4(Data.Color.xyz, 1.0);

} ENDPROGRAM
