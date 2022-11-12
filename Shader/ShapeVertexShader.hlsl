#include	"psvscommon.fx"
 
VS_OUTPUT main(float4 Pos : POSITION,
    float4 Color : COLOR,
    float4 Normal : NORMAL)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    float4 N = Normal;
    N.w = 0.0f; // 法線はベクトルなのでＷの値を０にする。

    N = mul(N, World);
    N = normalize(N);
    output.Normal = N;
    output.Color = Color;

    return output;
}