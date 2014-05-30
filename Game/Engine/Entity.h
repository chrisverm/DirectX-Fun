// ---------------------------------------------------------------------------
// Entity.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/30/2014
// ---------------------------------------------------------------------------

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "DXMath.h"
#include "Mesh.h"
#include "Material.h"

class Entity
{
public:
	Vector3 Position, Scale;
	Quaternion Orientation;

	Entity();
	virtual ~Entity();

	virtual void Initialize(ID3D11Buffer* modelConstBuffer);
	virtual void Update(float dt);
	void SetConstantBuffer(ID3D11DeviceContext* deviceContext, void* data);
	bool AttachTo(Entity* parent, bool applyParentMatrix = true);

protected:
	XMFLOAT4X4 worldMatrix;

	ID3D11Buffer* modelConstBuffer;

	Entity* parent;
	bool applyParentMatrix;

private:
	std::vector<Entity*> children;

	bool AddChild(Entity* child);
	bool RemoveChild(Entity* child, bool release = true);

};

#endif