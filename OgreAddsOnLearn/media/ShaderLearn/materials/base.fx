//dx11   hlsl 
struct VS_IN
{
	float4 position		: POSITION;
	//float3 normal		: NORMAL;
	float2 tcoord		: TEXCOORD0;
};

struct VS_OUT
{
	float4 position		: SV_POSITION;
	float2 tcoord		: TEXCOORD0;
};

//uniform float4x4 matWV;
uniform float4x4 matWVP;
//uniform float4 gdiffuse;
//uniform float4 gspecular;
//uniform float4 gambient;

VS_OUT main_vs(VS_IN In)
{
    VS_OUT Out = (VS_OUT)0;
    
    // transfrom
    Out.position = mul(matWVP,In.position);

    //copy tcoord
    Out.tcoord = In.tcoord;
    return Out;
}


struct PS_IN
{
	float4 position		: SV_POSITION;
    float2 tcoord 		: TEXCOORD0;
};

struct PS_OUT
{
    float4 color	: COLOR0;
};

Texture2D txDiffuse : register( t0 );

//Texture2D tex;
SamplerState ss;
float4 main_ps(PS_IN In) : SV_Target
{
   // PS_OUT Out;
   // Out.color = txDiffuse.Sample(ss, In.tcoord);
  //  return Out;
  float4 color = txDiffuse.Sample(ss, In.tcoord);
  return color;
}