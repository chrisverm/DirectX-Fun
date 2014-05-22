// ---------------------------------------------------------------------------
// Entity.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/18/2014
// ---------------------------------------------------------------------------

#include "Entity.h"

Entity::Entity()
{
	position	= Vector3::Zero();
	orientation = Quaternion::Identity();
	scale		= Vector3(1.0f, 1.0f, 1.0f);

	modelConstBuffer = nullptr;
	parent = nullptr;
}

Entity::~Entity()
{
	for (int i = children.size(); i > 0; i--)
		RemoveChild(children[i - 1]);
}

void Entity::Initialize(ID3D11Buffer* modelConstBuffer)
{
	this->modelConstBuffer = modelConstBuffer;
}

void Entity::Update(float dt)
{
	XMMATRIX trans  = XMMatrixTranslationFromVector(position);
	XMMATRIX rot	= XMMatrixRotationQuaternion(orientation);
	XMMATRIX sca	= XMMatrixScalingFromVector(scale);
	XMMATRIX world	= sca * rot * trans;

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(world));
}

void Entity::SetConstantBuffer(ID3D11DeviceContext* deviceContext, void* data)
{
	deviceContext->UpdateSubresource(
		modelConstBuffer,
		0,
		NULL,
		data,
		0,
		0);
}

bool Entity::AttachTo(Entity* parent, bool applyParentMatrix)
{
	if (parent == this || this->parent != nullptr) 
		return false;

	if (parent->AddChild(this))
	{
		this->parent = parent;
		this->applyParentMatrix = applyParentMatrix;
	}

	return true;
}

bool Entity::AddChild(Entity* child)
{
	children.push_back(child);

	return true;
}

bool Entity::RemoveChild(Entity* child, bool release)
{
	std::vector<Entity*>::iterator it = 
		std::find(children.begin(), children.end(), child);

	if (it == children.end()) // child does not exist in vector of children
		return false;

	children.erase(it);

	if (release) delete child;

	return true;
}