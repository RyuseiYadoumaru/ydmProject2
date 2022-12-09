#include "Common.hlsli"

VS_OUTPUT main(float4 Pos : POSITION, float4 color : COLOR)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    Pos.w = 1.0f;
    float4 worldTrans = mul(Pos, World);
    float4 viewTrans = mul(worldTrans, View);
    output.Pos = mul(viewTrans, Projection);
    output.Color = color;
    return output;
}