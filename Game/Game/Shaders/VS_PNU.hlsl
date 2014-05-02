#include "ConstantBuffers.hlsli"

struct VSInput
{
	float3 position : POSITION0;
};

struct VertexToPixel
{
	float4 position : SV_POSITION;
};

VertexToPixel main( VSInput input )
{
	VertexToPixel output;

	// Calculate output position
	matrix worldViewProj = mul(mul(world, view), projection);
	output.position = mul(float4(input.position, 1.0f), worldViewProj);

	return output;
}