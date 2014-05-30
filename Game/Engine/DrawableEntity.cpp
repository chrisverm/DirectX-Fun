// ---------------------------------------------------------------------------
// DrawableEntity.cpp by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/30/2014
// ---------------------------------------------------------------------------

#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(Mesh* mesh, Material* material)
	: Entity()
{
	this->mesh = mesh;
	this->material = material;
}

DrawableEntity::~DrawableEntity() { }

void DrawableEntity::Render(ID3D11DeviceContext* deviceContext)
{
	mesh->SetBuffers(deviceContext);
	material->SetShaders(deviceContext);
}