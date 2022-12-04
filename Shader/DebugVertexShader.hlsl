#include "Common.hlsli"

VS_OUTPUT main(	float4 Pos : POSITION, float4 color : COLOR)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    Pos.w = 1.0f;
    output.Pos = mul(Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Color = color;
    return output;
}