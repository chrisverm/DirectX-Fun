// ---------------------------------------------------------------------------
// Crate.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/18/2014
// ---------------------------------------------------------------------------

#ifndef CRATE_H
#define CRATE_H

#include "DrawableEntity.h"
#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffers.h"

class Crate : public DrawableEntity
{
public:
	Crate(Mesh* mesh, Material* material);
	~Crate();

	void Initialize(ID3D11Buffer* modelConstBuffer, PerModelData* modelConstBufferData);
	void Update(float dt);
	void Render(ID3D11DeviceContext* deviceContext);

private:
	PerModelData* modelConstBufferData;

};

#endif