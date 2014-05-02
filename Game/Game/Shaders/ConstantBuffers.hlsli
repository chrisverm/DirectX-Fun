#ifndef CONSTANT_BUFFERS_HLSLI
#define CONSTANT_BUFFERS_HLSLI

cbuffer perFrame : register( b0 )
{
	matrix view;
	matrix projection;
};

cbuffer perModel : register( b1 )
{
	matrix world;
};

#endif