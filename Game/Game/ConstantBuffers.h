// ---------------------------------------------------------------------------
// ConstantBuffers.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/02/2014
// ---------------------------------------------------------------------------

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