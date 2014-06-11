// ---------------------------------------------------------------------------
// ConstantBuffers.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 6/11/2014
// ---------------------------------------------------------------------------

#ifndef CONSTANT_BUFFERS_H
#define CONSTANT_BUFFERS_H

#include <DirectXMath.h>
#include "DXMath.h"

using namespace DirectX;

struct PerFrameData
{
	Matrix4 view;
	Matrix4 projection;
};

struct PerModelData
{
	Matrix4 model;
};

#endif