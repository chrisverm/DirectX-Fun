// ---------------------------------------------------------------------------
// MoveableEntity.h by Christopher Vermilya (C) 2014 All Rights Reserved.
// last edited 5/19/2014
// ---------------------------------------------------------------------------

#ifndef MOVEABLE_ENTITY_H
#define MOVEABLE_ENTITY_H

#include "DrawableEntity.h"

class MoveableEntity : public DrawableEntity
{
public:
	MoveableEntity(Mesh* mesh, Material* material);
	virtual ~MoveableEntity();

	virtual void Update(float dt);

protected:
	Vector3 linearVel, linearAccel;
	Clamps1 linearVelClamps, linearAccelClamps;
	Vector3 angularVel, angularAccel;
	Clamps1 angularVelClamps, angularAccelClamps;

};

#endif