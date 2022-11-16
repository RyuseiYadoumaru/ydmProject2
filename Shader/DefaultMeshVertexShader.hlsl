#include "Common.hlsli"


VS_OUTPUT main(float4 Pos : POSITION,
    float4 Color : COLOR,
    float2 Tex : TEXCOORD,
	float4 Normal : NORMAL)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    output.Pos = mul(Pos, World);
    output.WPos = output.Pos;
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    
    output.Color = Color;

    float4 N = Normal;
    N.w = 0.0f; // �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���
    N = mul(N, World);
    N = normalize(N);
    output.Normal = N;

    output.Tex = Tex;
    return output;
}