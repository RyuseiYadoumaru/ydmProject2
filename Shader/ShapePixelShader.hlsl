#include	"psvscommon.fx"

float4 main(VS_OUTPUT input) : SV_Target
{
    float4 col = input.Color;
    col.a = 1.0f;
    return col;
}

