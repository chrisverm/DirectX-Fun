#include "ConstantBuffers.hlsli"

struct VSInput
{
	float3 position : POSITION0;
	float3 normal	: NORMAL0;
	float2 uv		: TEXCOORD0;
};

struct VertexToPixel
{
	float4 position : SV_POSITION;
	float3 normal	: NORMAL0;
	float2 uv		: TEXCOORD0;
};

VertexToPixel main( VSInput input )
{
	VertexToPixel output;

	// Calculate output position
	matrix worldViewProj = mul(mul(world, view), projection);
	output.position = mul(float4(input.position, 1.0f), worldViewProj);

	output.normal	= mul(input.normal, (float3x3)world);
	output.uv		= input.uv;

	return output;
}