// ---------------------------------------------------------------------------
// Entity.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/22/2014
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
	Entity();
	virtual ~Entity();

	virtual void Initialize(ID3D11Buffer* modelConstBuffer);
	virtual void Update(float dt);
	void SetConstantBuffer(ID3D11DeviceContext* deviceContext, void* data);
	bool AttachTo(Entity* parent, bool applyParentMatrix = true);

protected:
	Vector3 position, scale;
	Quaternion orientation;
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