#ifndef LIGHTING_HLSLI
#define LIGHTING_HLSLI

struct Light
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
};

struct DirectionalLight : Light
{
	float3 Direction;
	float  padding;
};

/* Methods */

void ComputeDirectionalLight(DirectionalLight light, float3 normal,
							 out float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec	= float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightDirection = normalize(light.Direction);
	float nDotL = saturate(dot(normal, -lightDirection));

	diffuse += light.Diffuse * nDotL;
}

#endif