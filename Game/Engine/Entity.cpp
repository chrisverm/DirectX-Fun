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
}

Entity::~Entity() { }

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