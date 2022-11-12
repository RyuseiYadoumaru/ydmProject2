#include	"psvscommon.fx"

float4 main(VS_OUTPUT input) : SV_Target
{
    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
    float4 col = texcol;
    col.a = 1.0f;
    return col;
}

