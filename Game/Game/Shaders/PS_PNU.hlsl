#include "Lighting.hlsli"

Texture2D myTexture : register( t0 );
SamplerState mySampler : register( s0 );

struct VertexToPixel
{
	float4 position : SV_POSITION;
	float3 normal	: NORMAL0;
	float2 uv		: TEXCOORD0;
};

float4 main( VertexToPixel input ) : SV_TARGET
{
	float4 ambient	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 A, D, S;

	DirectionalLight dirLight;
	dirLight.Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	dirLight.Direction = normalize(float3(0.0f, 0.0f, 1.0f));

	ComputeDirectionalLight(dirLight, input.normal, A, D, S);
	ambient  += A;
	diffuse	 += D;
	specular += S;

	return myTexture.Sample(mySampler, input.uv) * (ambient + diffuse + specular);
}