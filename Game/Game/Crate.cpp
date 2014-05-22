// ---------------------------------------------------------------------------
// Crate.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/19/2014
// ---------------------------------------------------------------------------

#include "Crate.h"

Crate::Crate(Mesh* mesh, Material* material)
	: MoveableEntity(mesh, material) { }

Crate::~Crate() { }

void Crate::Initialize(ID3D11Buffer* modelConstBuffer, PerModelData* modelConstBufferData)
{
	Entity::Initialize(modelConstBuffer);

	this->modelConstBufferData = modelConstBufferData;

	angularAccel.X += 22.5f * DegsToReds;
	angularAccel.Y += 45.0f * DegsToReds;
	angularAccel *= 1.5f;
}

void Crate::Update(float dt)
{
	MoveableEntity::Update(dt);

	modelConstBufferData->model = worldMatrix;
}

void Crate::Render(ID3D11DeviceContext* deviceContext)
{
	SetConstantBuffer(deviceContext, modelConstBufferData);

	DrawableEntity::Render(deviceContext);

	deviceContext->DrawIndexed(
		mesh->NumIndices,
		0,
		0);
}