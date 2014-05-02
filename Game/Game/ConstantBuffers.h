#ifndef CONSTANT_BUFFERS_H
#define CONSTANT_BUFFERS_H

#include <DirectXMath.h>

using namespace DirectX;

struct PerFrameData
{
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

struct PerModelData
{
	XMFLOAT4X4 model;
};

#endif