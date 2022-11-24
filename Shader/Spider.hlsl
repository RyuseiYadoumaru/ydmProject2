#include	"Common.hlsli"

float4 main(VS_OUTPUT input) : SV_Target
{
    float4 result;
    
    float4 col1, col2, col3;
    col1 = float4(0.2f, 0.2f, 0.2f, 1.0f);
    col3 = float4(0.01f, 0.01f, 0.01f, 1.0f);
    col2 = float4(0.1f, 0.1f, 0.1f, 1.0f);
    
    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
    
    result = texcol.g * col1 + texcol.r * col2 + texcol.b * col3;
    result.a = 1.0f;
    return result;
}