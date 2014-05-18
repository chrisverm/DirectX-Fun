// ---------------------------------------------------------------------------
// Crate.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/17/2014
// ---------------------------------------------------------------------------

#include "Crate.h"

Crate::Crate(Mesh* mesh, Material* material)
	: Entity()
{
	this->mesh = mesh;
	this->material = material;
}

Crate::~Crate()
{
	if (mesh != nullptr)
	{
		delete mesh;
		mesh = nullptr;
	}

	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}

	Entity::~Entity();
}

void Crate::Initialize(ID3D11Buffer* modelConstBuffer, PerModelData* modelConstBufferData)
{
	Entity::Initialize(modelConstBuffer);

	this->modelConstBufferData = modelConstBufferData;
}

void Crate::Update(float dt)
{
	orientation *= Quaternion::FromRollPitchYaw(22.5f * DegsToReds * dt, 
												45.0f * DegsToReds * dt, 
												0.0f);

	Entity::Update(dt);

	modelConstBufferData->model = worldMatrix;
}

void Crate::Render(ID3D11DeviceContext* deviceContext)
{
	SetConstantBuffer(deviceContext, modelConstBufferData);

	mesh->SetBuffers(deviceContext);
	material->SetShaders(deviceContext);

	deviceContext->DrawIndexed(
		mesh->NumIndices,
		0,
		0);
}