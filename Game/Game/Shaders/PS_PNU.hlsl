
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
	return float4(1, 1, 1, 1);// myTexture.Sample(mySampler, input.uv);
}