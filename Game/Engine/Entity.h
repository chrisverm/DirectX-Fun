// ---------------------------------------------------------------------------
// Entity.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/17/2014
// ---------------------------------------------------------------------------

#ifndef ENTITY_H
#define ENTITY_H

#include "DXMath.h"
#include "Mesh.h"
#include "Material.h"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void Initialize(ID3D11Buffer* modelConstBuffer);
	virtual void Update(float dt);
	virtual void SetConstantBuffer(ID3D11DeviceContext* deviceContext, void* data);

protected:
	Vector3 position;
	Quaternion orientation;
	Vector3 scale;
	XMFLOAT4X4 worldMatrix;

	ID3D11Buffer* modelConstBuffer;

};

#endif