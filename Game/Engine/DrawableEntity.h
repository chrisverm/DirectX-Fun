// ---------------------------------------------------------------------------
// DrawableEntity.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/18/2014
// ---------------------------------------------------------------------------

#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include "Entity.h"
#include "Mesh.h"
#include "Material.h"

class DrawableEntity : public Entity
{
public:
	DrawableEntity(Mesh* mesh, Material* material);
	virtual ~DrawableEntity();

	virtual void Render(ID3D11DeviceContext* deviceContext);

protected:
	Mesh* mesh;
	Material* material;

};

#endif